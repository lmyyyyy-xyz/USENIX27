use pyo3::prelude::*;

mod bp;
mod constants;
mod greedy;
mod llo;
mod py_bp;
mod py_greedy;
mod py_prob_bp;
mod rhs;
mod util;

#[pymodule]
fn hint_solver(m: &Bound<'_, PyModule>) -> PyResult<()> {
    m.add_class::<py_bp::PyBP>()?;
    m.add_class::<py_prob_bp::PyProbBP>()?;
    m.add_class::<py_greedy::PyGreedy>()?;
    Ok(())
}
