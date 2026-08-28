use num_complex::Complex;

pub fn llo<const SZ_MSG: usize>(out: &mut Vec<Vec<Complex<f64>>>, inp: Vec<Vec<Complex<f64>>>) {
    let mut acc_fwd = inp.first().unwrap().clone();
    let mut acc_bwd = inp.last().unwrap().clone();
    let n = out.len();
    for l in 1..n {
        out[l]
            .iter_mut()
            .zip(acc_fwd.iter())
            .for_each(|(o, a)| *o *= a);
        acc_fwd
            .iter_mut()
            .zip(inp[l].iter())
            .for_each(|(o, a)| *o *= a);
    }
    for l in (0..n - 1).rev() {
        out[l]
            .iter_mut()
            .zip(acc_bwd.iter())
            .for_each(|(o, a)| *o *= a);
        acc_bwd
            .iter_mut()
            .zip(inp[l].iter())
            .for_each(|(o, a)| *o *= a);
    }
}

pub fn llo_prior<const SZ_MSG: usize>(
    out: &mut [[f64; SZ_MSG]],
    inp: &[Vec<[f64; SZ_MSG]>],
    prior: [f64; SZ_MSG],
    i: usize,
    connections_var: &Vec<usize>,
    connections_fac_inv: &Vec<Vec<usize>>,
) {
    let mut acc_fwd = prior;
    let mut acc_bwd = [1f64; SZ_MSG];
    let nfac = out.len();
    for j in 0..nfac {
        let current_fac_node = connections_var[j];
        let rel_var_node = connections_fac_inv[current_fac_node][i];
        out[j]
            .iter_mut()
            .zip(acc_fwd.iter())
            .for_each(|(o, a)| *o *= a);
        acc_fwd
            .iter_mut()
            .zip(inp[current_fac_node][rel_var_node].iter())
            .for_each(|(o, a)| *o *= a);
    }
    for j in (0..nfac).rev() {
        let current_fac_node = connections_var[j];
        let rel_var_node = connections_fac_inv[current_fac_node][i];
        out[j]
            .iter_mut()
            .zip(acc_bwd.iter())
            .for_each(|(o, a)| *o *= a);
        acc_bwd
            .iter_mut()
            .zip(inp[current_fac_node][rel_var_node].iter())
            .for_each(|(o, a)| *o *= a);
    }
}
