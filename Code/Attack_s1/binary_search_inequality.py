#!/usr/bin/env python3
"""Run the requested Dilithium2 inequality constraint-count binary search.

Running this file without arguments is equivalent to:

    python binary_search_constraints.py --level 2
        --constraint-mode inequality --threshold gamma1-beta
        --signatures 1000000 --min-constraints-per-poly 500
        --max-constraints-per-poly 2000 --bp-iterations 20
        --bp-damping 0 --threads 16 --seed 1

Additional command-line arguments are appended after these defaults, so a
default can be overridden, for example ``--seed 2`` or ``--no-save``.
"""

from __future__ import annotations

import sys

from binary_search_constraints import main as run_binary_search


DEFAULT_ARGUMENTS = [
    "--level",
    "2",
    "--constraint-mode",
    "inequality",
    "--threshold",
    "gamma1-beta",
    "--signatures",
    "1000000",
    "--min-constraints-per-poly",
    "500",
    "--max-constraints-per-poly",
    "2000",
    "--bp-iterations",
    "20",
    "--bp-damping",
    "0",
    "--threads",
    "16",
    "--seed",
    "1",
]


def main(argv: list[str] | None = None) -> int:
    overrides = sys.argv[1:] if argv is None else argv
    return run_binary_search([*DEFAULT_ARGUMENTS, *overrides])


if __name__ == "__main__":
    raise SystemExit(main())
