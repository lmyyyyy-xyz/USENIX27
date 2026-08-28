use std::usize;

use num_complex::Complex;
use rayon::prelude::*;
use rustfft::FftPlanner;

use crate::llo::*;
use crate::rhs::*;
use crate::util::*;

pub struct BP<const SZ_MSG: usize, RHS: Rhs<SZ_MSG>> {
    fac_results: Vec<Vec<[f64; SZ_MSG]>>, //[[f64; SZ_MSG]; NVAR]; NFAC],
    var_results: Vec<Vec<[f64; SZ_MSG]>>, //[[[f64; SZ_MSG]; NVAR]; NFAC],
    nfac: usize,
    nvar: usize,
    prior: [f64; SZ_MSG],
    niter: usize,
    chk_coeff: Vec<Vec<i32>>,
    chk_rhs: Vec<RHS>, //[RHS; NFAC],
    chk_sz: Vec<usize>,
    connections_fac: Vec<Vec<usize>>, //fac node -> local index vnode -> gloabl index vnode
    connections_fac_inv: Vec<Vec<usize>>, //fac node -> global index vnode -> local index vnode
    connections_var: Vec<Vec<usize>>, // var node -> local index fnode -> global index fnode
    connections_var_inv: Vec<Vec<usize>>, // var node -> global index fnode -> local index fnode
}

pub fn normalize(msg: &mut [f64]) {
    let max = msg
        .iter()
        .max_by(|a, b| a.partial_cmp(b).expect("Failed to normalize"))
        .expect("Failed to normalize")
        .clone();
    if max > 0.0 {
        msg.iter_mut().for_each(|x| *x /= max)
    } else {
        msg.iter_mut().for_each(|x| *x = 1.0)
    }
}

pub fn to_probabilities(msg: &mut [f64]) {
    let sum: f64 = msg.iter().sum();
    if sum > 0.0 {
        msg.iter_mut().for_each(|x| *x /= sum)
    } else {
        let l = 1.0 / msg.len() as f64;
        msg.iter_mut().for_each(|x| *x = l)
    }
}

fn normalize_complex(msg: &mut [Complex<f64>]) {
    let m: f64 = msg
        .iter()
        .map(|x| x.norm())
        .max_by(|a, b| a.partial_cmp(b).expect("Failed to normalize fft."))
        .expect("Failed to normalize fft.");
    if m > 0.0 {
        msg.iter_mut().for_each(|x| *x /= m);
    } else {
        msg.iter_mut()
            .for_each(|x| *x = Complex::<f64> { re: 1.0, im: 0.0 })
    }
}

impl<const SZ_MSG: usize> BP<SZ_MSG, ValueRhs<SZ_MSG>> {
    pub fn initialize_value(
        prior: [f64; SZ_MSG],
        coeff: Vec<Vec<i32>>,
        rhs: Vec<Vec<(i32, f64)>>,
        chk_sz: Option<Vec<usize>>,
    ) -> Self {
        let rhs_rhs = rhs.into_iter().map(|x| ValueRhs { values: x }).collect();
        Self::initialize(prior, coeff, rhs_rhs, chk_sz)
    }
}

impl<const SZ_MSG: usize> BP<SZ_MSG, ProbValueRhs<SZ_MSG>> {
    pub fn initialize_prob_value(
        prior: [f64; SZ_MSG],
        coeff: Vec<Vec<i32>>,
        rhs: Vec<Vec<(i32, f64)>>,
        p: Vec<f64>,
        chk_sz: Option<Vec<usize>>,
    ) -> Self {
        let rhs_rhs = rhs
            .into_iter()
            .zip(p.into_iter())
            .map(|(x, p)| ProbValueRhs { p: p, values: x })
            .collect();
        Self::initialize(prior, coeff, rhs_rhs, chk_sz)
    }
}

impl<const SZ_MSG: usize, RHS: Rhs<SZ_MSG> + Sync> BP<SZ_MSG, RHS> {
    pub fn initialize(
        mut prior: [f64; SZ_MSG],
        coeff: Vec<Vec<i32>>,
        mut rhs: Vec<RHS>,
        chk_sz: Option<Vec<usize>>,
    ) -> Self {
        let nfac = coeff.len();
        let nvar = coeff[0].len();
        let mut fac_results = Vec::new();
        let mut var_results = Vec::new();
        let mut connections_fac = Vec::new();
        let mut connections_var = vec![Vec::new(); nvar];
        let mut connections_fac_inv = Vec::new();
        let mut connections_var_inv = vec![Vec::new(); nvar];
        for i in 0..nfac {
            assert!(
                coeff[i].len() == nvar,
                "Length of {i}-th equation does not match {nvar}."
            );
            let mut len = 0;
            let mut connections_i = Vec::new();
            let mut connections_i_inv = Vec::new();
            for j in 0..nvar {
                if coeff[i][j] == 0 {
                    connections_i_inv.push(usize::MAX);
                    continue;
                }
                connections_i_inv.push(len);
                len += 1;
                connections_i.push(j);
                connections_var[j].push(i);
            }
            connections_fac.push(connections_i);
            connections_fac_inv.push(connections_i_inv);
            fac_results.push(vec![[1.0; SZ_MSG]; len]);
            var_results.push(vec![[1.0; SZ_MSG]; len]);
        }
        for i in 0..nvar {
            let mut len = 0;
            for j in 0..nfac {
                if coeff[j][i] == 0 {
                    connections_var_inv[i].push(usize::MAX);
                    continue;
                }
                connections_var_inv[i].push(len);
                len += 1;
            }
        }

        let mut sums_lens = Vec::new();
        let chk_sz = if let Some(chk_sz) = chk_sz {
            chk_sz
        } else {
            for coeff_i in &coeff {
                let mut sum = 0;
                for c in coeff_i {
                    sum += c.abs() as usize * SZ_MSG / 2;
                }
                sums_lens.push(f64::log2(sum as f64).ceil() as usize + 1);
            }
            sums_lens
        };
        for rhs_i in &mut rhs {
            rhs_i.normalize();
        }
        normalize(&mut prior);
        Self {
            prior,
            chk_coeff: coeff,
            niter: 0,
            fac_results,
            var_results,
            chk_rhs: rhs,
            chk_sz,
            nfac,
            nvar,
            connections_fac,
            connections_var,
            connections_fac_inv,
            connections_var_inv,
        }
    }

    pub fn get_chk_sz(&self) -> Vec<usize> {
        self.chk_sz.clone()
    }

    pub fn get_results(&self) -> Vec<Vec<f64>> {
        (0..self.nvar)
            .into_par_iter()
            .map(|i| {
                let mut res = vec![1.0; SZ_MSG];
                for j in &self.connections_var[i] {
                    for k in 0..SZ_MSG {
                        res[k] *= self.fac_results[*j][self.connections_fac_inv[*j][i]][k];
                    }
                }
                for k in 0..SZ_MSG {
                    res[k] *= self.prior[k];
                }
                to_probabilities(&mut res);
                res
            })
            .collect()
    }

    pub fn get_results_and_entropy(&self) -> Vec<(Vec<f64>, f64)> {
        (0..self.nvar)
            .into_par_iter()
            .map(|i| {
                let mut res = vec![1.0; SZ_MSG];
                for j in &self.connections_var[i] {
                    for k in 0..SZ_MSG {
                        res[k] *= self.fac_results[*j][self.connections_fac_inv[*j][i]][k];
                    }
                }
                for k in 0..SZ_MSG {
                    res[k] *= self.prior[k];
                }
                to_probabilities(&mut res);
                let ent = entropy(&res);
                (res, ent)
            })
            .collect()
    }

    pub fn normalize_fac(&mut self) {
        self.fac_results.par_iter_mut().for_each(|v_res| {
            for i in 0..v_res.len() {
                normalize(&mut v_res[i]);
            }
        });
    }

    pub fn normalize_var(&mut self) {
        self.var_results.par_iter_mut().for_each(|v_res| {
            for i in 0..v_res.len() {
                to_probabilities(&mut v_res[i]);
            }
        });
    }

    pub fn propagate(&mut self) {
        self.propagate_fac();
        self.normalize_fac();
        self.propagate_var();
        self.normalize_var();
        self.niter += 1;
    }

    /// Run one BP iteration with convex message damping.
    ///
    /// `damping` is the weight retained from the previous message:
    ///     damped = damping * old + (1-damping) * computed.
    /// Values must satisfy 0 <= damping < 1. A value of zero is identical to
    /// `propagate()`.
    pub fn propagate_damped(&mut self, damping: f64) {
        assert!(
            damping.is_finite() && (0.0..1.0).contains(&damping),
            "damping must satisfy 0 <= damping < 1"
        );
        if damping == 0.0 {
            self.propagate();
            return;
        }

        let keep_new = 1.0 - damping;
        let old_fac = self.fac_results.clone();
        self.propagate_fac();
        self.normalize_fac();
        self.fac_results
            .par_iter_mut()
            .zip(old_fac.par_iter())
            .for_each(|(new_rows, old_rows)| {
                for (new_msg, old_msg) in new_rows.iter_mut().zip(old_rows.iter()) {
                    for state in 0..SZ_MSG {
                        new_msg[state] = damping * old_msg[state] + keep_new * new_msg[state];
                    }
                }
            });
        self.normalize_fac();

        let old_var = self.var_results.clone();
        self.propagate_var();
        self.normalize_var();
        self.var_results
            .par_iter_mut()
            .zip(old_var.par_iter())
            .for_each(|(new_rows, old_rows)| {
                for (new_msg, old_msg) in new_rows.iter_mut().zip(old_rows.iter()) {
                    for state in 0..SZ_MSG {
                        new_msg[state] = damping * old_msg[state] + keep_new * new_msg[state];
                    }
                }
            });
        self.normalize_var();
        self.niter += 1;
    }

    pub fn get_fac_results(&self) -> Vec<Vec<[f64; SZ_MSG]>> {
        self.fac_results.clone()
    }

    pub fn get_var_results(&self) -> Vec<Vec<[f64; SZ_MSG]>> {
        self.var_results.clone()
    }

    pub fn fill_fac_results(&mut self) {
        self.fac_results.par_iter_mut().for_each(|v_var| {
            for msg in v_var.iter_mut() {
                msg.fill(0.0);
            }
        });
    }

    pub fn propagate_var(&mut self) {
        let res: Vec<Vec<[f64; SZ_MSG]>> = (0..self.nvar)
            .into_par_iter()
            .map(|i| {
                let mut output = vec![[1f64; SZ_MSG]; self.connections_var[i].len()];
                llo_prior::<SZ_MSG>(
                    &mut output,
                    &self.fac_results,
                    self.prior.clone(),
                    i,
                    &self.connections_var[i],
                    &self.connections_fac_inv,
                );
                output
            })
            .collect();

        for j in 0..self.nfac {
            for i in 0..self.connections_fac[j].len() {
                let local_vnode = self.connections_fac[j][i];

                for l in 0..SZ_MSG {
                    self.var_results[j][i][l] =
                        res[local_vnode][self.connections_var_inv[local_vnode][j]][l];
                }
            }
        }
    }

    pub fn propagate_fac(&mut self) {
        self.fill_fac_results();
        self.fac_results
            .par_iter_mut()
            .enumerate()
            .for_each(|(j, f_res)| {
                let coeffs_len = self.connections_fac[j].len();
                let mut chk_mem_fft =
                    vec![vec![Complex { re: 0.0, im: 0.0 }; 1 << self.chk_sz[j]]; coeffs_len];
                let mut planner = FftPlanner::new();
                let fft = planner.plan_fft_forward(1 << self.chk_sz[j]);
                for i in 0..coeffs_len {
                    let coeff = self.chk_coeff[j][self.connections_fac[j][i]];
                    chk_enlarge_and_mult(
                        &mut chk_mem_fft[i],
                        &self.var_results[j][i],
                        coeff,
                        SZ_MSG,
                        self.chk_sz[j],
                    );
                    assert!(
                        chk_mem_fft[i].iter().map(|x| x.norm()).sum::<f64>() > 0.001,
                        "{:?}\n, j={:?}, i={:?}",
                        self.var_results[j][i],
                        j,
                        i
                    );
                    fft.process(&mut chk_mem_fft[i]);
                    normalize_complex(&mut chk_mem_fft[i]);
                }
                let mut chk_mem_fft_llo =
                    vec![vec![Complex { re: 1.0, im: 0.0 }; 1 << self.chk_sz[j]]; coeffs_len];
                llo::<SZ_MSG>(&mut chk_mem_fft_llo, chk_mem_fft);
                let mut planner = FftPlanner::new();
                let ifft = planner.plan_fft_inverse(1 << self.chk_sz[j]);
                for i in 0..coeffs_len {
                    normalize_complex(&mut chk_mem_fft_llo[i]);
                    ifft.process(&mut chk_mem_fft_llo[i]);
                    chk_mem_fft_llo[i]
                        .iter_mut()
                        .for_each(|x| x.re = x.re.abs());
                    normalize_complex(&mut chk_mem_fft_llo[i]);
                }
                self.chk_rhs[j].compute_msg_from_sumdist(
                    f_res,
                    chk_mem_fft_llo,
                    &self.chk_coeff[j],
                    SZ_MSG,
                    self.chk_sz[j],
                    &self.connections_fac[j],
                );
            });
    }

    pub fn get_nfac(&self) -> usize {
        self.nfac
    }

    pub fn get_iteration(&self) -> usize {
        self.niter
    }

    pub fn get_prior(&self) -> Vec<f64> {
        self.prior.to_vec()
    }
}
