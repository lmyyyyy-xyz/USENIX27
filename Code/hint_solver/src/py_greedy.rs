use pyo3::prelude::*;
use std::thread::available_parallelism;

use crate::constants::SZ_MSG;
use crate::greedy::Greedy;
use crate::util::create_pool;

#[pyclass]
pub struct PyGreedy {
    greedy: Greedy,
    thread_pool: rayon::ThreadPool,
    actions: Vec<(i64, f64, usize)>,
}

#[pymethods]
impl PyGreedy {
    #[new]
    #[pyo3(signature = (coeffs, rhs))]
    fn new(coeffs: Vec<Vec<i64>>, rhs: Vec<Vec<(i64, f64)>>) -> Self {
        let nthr = available_parallelism().unwrap().get();
        let thread_pool = create_pool(nthr / 2);
        let nvar = coeffs[0].len();
        let eta = SZ_MSG / 2;
        let mut actions = vec![(0, f64::INFINITY, 0); nvar];
        for i in 0..nvar {
            actions[i] = (0, f64::INFINITY, i);
        }
        let greedy = Greedy::initialize(vec![0; nvar], coeffs, rhs, eta as i64);
        Self {
            greedy,
            thread_pool,
            actions,
        }
    }
    fn solve(&mut self, num_changes: usize) {
        self.actions = self.thread_pool.install(|| self.greedy.solve(num_changes));
    }

    fn get_guess(&self) -> Vec<i64> {
        self.greedy.get_guess()
    }

    fn get_actions(&self) -> Vec<(i64, f64, usize)> {
        self.actions.clone()
    }

    fn get_nthreads(&self) -> usize {
        self.thread_pool.current_num_threads()
    }

    fn set_nthreads(&mut self, nthreads: usize) {
        let pool = create_pool(nthreads);
        self.thread_pool = pool;
    }
}
