use pyo3::prelude::*;
use std::thread::available_parallelism;

use crate::bp::BP;
use crate::constants::{NVAR, SZ_MSG};
use crate::rhs::ProbValueRhs;
use crate::util::{create_pool, to_array};

#[pyclass]
pub struct PyProbBP {
    bp: BP<SZ_MSG, ProbValueRhs<SZ_MSG>>,
    thread_pool: rayon::ThreadPool,
}

#[pymethods]
impl PyProbBP {
    #[new]
    #[pyo3(signature = (coeffs, rhs, p, sz_chk=None, prior=None))]
    fn new(
        coeffs: Vec<Vec<i32>>,
        rhs: Vec<Vec<(i32, f64)>>,
        p: Vec<f64>,
        sz_chk: Option<usize>,
        prior: Option<Vec<f64>>,
    ) -> Self {
        let prior = prior.unwrap_or(vec![1.0; SZ_MSG]);
        let n = coeffs.len();
        let nthr = available_parallelism().unwrap().get();
        let pool = create_pool(nthr / 2);
        let sz_chk = sz_chk.map(|x| vec![x; n]);
        Self {
            bp: BP::initialize_prob_value(
                to_array::<f64, SZ_MSG>(prior).expect("Prior has wrong size."),
                coeffs,
                rhs,
                p,
                sz_chk,
            ),
            thread_pool: pool,
        }
    }

    fn get_chk_sz(&self) -> Vec<usize> {
        self.bp.get_chk_sz()
    }

    fn get_nthreads(&self) -> usize {
        self.thread_pool.current_num_threads()
    }

    fn set_nthreads(&mut self, nthreads: usize) {
        let pool = create_pool(nthreads);
        self.thread_pool = pool;
    }

    fn get_prior(&self) -> Vec<f64> {
        self.bp.get_prior()
    }

    fn get_nfac(&self) -> usize {
        self.bp.get_nfac()
    }

    fn get_nvar(&self) -> usize {
        NVAR
    }

    fn get_fac_results(&self) -> Vec<Vec<Vec<f64>>> {
        self.bp
            .get_fac_results()
            .into_iter()
            .map(|x| x.into_iter().map(|x| x.to_vec()).collect())
            .collect()
    }

    fn get_var_results(&self) -> Vec<Vec<Vec<f64>>> {
        self.bp
            .get_var_results()
            .into_iter()
            .map(|x| x.into_iter().map(|x| x.to_vec()).collect())
            .collect()
    }

    fn propagate_fac(&mut self) {
        self.thread_pool.install(|| self.bp.propagate_fac())
    }

    fn propagate_var(&mut self) {
        self.thread_pool.install(|| self.bp.propagate_var())
    }
    fn normalize_var(&mut self) {
        self.thread_pool.install(|| self.bp.normalize_var())
    }

    fn normalize_fac(&mut self) {
        self.thread_pool.install(|| self.bp.normalize_fac())
    }

    fn get_results(&mut self) -> Vec<Vec<f64>> {
        self.thread_pool.install(|| self.bp.get_results())
    }

    fn propagate(&mut self) {
        self.thread_pool.install(|| self.bp.propagate())
    }

    fn get_niter(&self) -> usize {
        self.bp.get_iteration()
    }
}
