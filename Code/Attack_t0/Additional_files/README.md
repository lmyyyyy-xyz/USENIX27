## Files

| Name                      | Description                                                       |
| :---                      | :---                                                              |
| `C_functions`             | C functions used for the attack                                   |
| `nistkat`                 | Contains the KAT for the three security level of Dilithium        |
| `Notebooks`                | Python Jupyter Notebook used to uncompress t0                     |
| `Dilithium_functions.py`  | Python implementation of Dilithium functions used for the attack  |
| `Dilithium_parameters.py` | Dilithium parameters                                              |
| `Helper_functions.py`     | Auxiliary functions used in the attack                            |

The `C_functions` directory also contains a shared noisy-equality module and
separate LP/hill-climbing build targets. It consumes the existing `(c,r0,h)`
signature pool; no additional sample-generation format is required.


