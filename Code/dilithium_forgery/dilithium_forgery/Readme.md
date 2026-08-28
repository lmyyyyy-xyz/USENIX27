# Signature-Forgery Experiment

## Experimental Environment

- Python 3.8.0
- Ubuntu 20.04.6 LTS
- OpenSSL 1.1.1f

## Dependency

- NumPy 1.24.4

## Usage

### 1. Prepare the Input Files

The `input_s1_pk_m` directory contains the input files
`meta_data_part{index}.npz`, `s1_true.txt`, and `pk_16.txt`. These files
provide the messages (`msg`), public key (`pk`), and secret component (`s1`)
used by the experiment.

To select different input values, modify the arguments passed to `read_data()`
in the `main` function of `forgery_signature.py`. The function returns a list
of messages, the public key as a string, and `s1` as a two-dimensional list.

The `forgery_sign()` function takes a message as a string, `s1` as a
two-dimensional list, and the public key as a string. It returns the forged
signature as a string.

Results are written to the `forgery_signature_output` directory. The file
`new_sm.txt` contains the forged signatures generated for multiple messages.

### 2. Run the Experiment

After configuring the file paths in the `main` function of
`forgery_signature.py` and installing the dependency, run:

```bash
python3 forgery_signature.py
```

The results will be available in the `forgery_signature_output` directory.
