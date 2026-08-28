"""Portable, anonymous path configuration for the SCA experiment scripts.

Every value can be overridden with an environment variable.  The defaults are
package-relative placeholders so the source tree never embeds a user name,
home directory, shared-storage account, or machine-specific project path.
"""

from __future__ import annotations

import os
from pathlib import Path


CODE_DIRECTORY = Path(__file__).resolve().parent


def _configured_path(variable: str, default: Path) -> str:
    configured = os.environ.get(variable)
    path = Path(configured).expanduser() if configured else default
    return str(path.resolve())


PACKAGE_ROOT = _configured_path(
    "REJ_SCA_PACKAGE_ROOT",
    CODE_DIRECTORY.parent,
)
SUPPORT_CODE_ROOT = _configured_path(
    "REJ_SCA_SUPPORT_ROOT",
    CODE_DIRECTORY,
)
ETS_ROOT = _configured_path(
    "REJ_SCA_ETS_ROOT",
    Path(PACKAGE_ROOT) / "data" / "ets",
)
TRACE_ROOT = _configured_path(
    "REJ_SCA_TRACE_ROOT",
    Path(PACKAGE_ROOT) / "data" / "traces",
)
EXTRACTED_TRACE_ROOT = _configured_path(
    "REJ_SCA_EXTRACTED_ROOT",
    Path(TRACE_ROOT) / "rej_2026_ntt_add_chk",
)
LABEL_ROOT = _configured_path(
    "REJ_SCA_LABEL_ROOT",
    Path(PACKAGE_ROOT) / "data" / "labels",
)
RESULTS_ROOT = _configured_path(
    "REJ_SCA_RESULTS_ROOT",
    Path(PACKAGE_ROOT) / "results",
)
MLDSA_SOURCE_ROOT = _configured_path(
    "REJ_SCA_MLDSA_SOURCE_ROOT",
    Path(PACKAGE_ROOT) / "external" / "dilithium_rej_filter",
)

NTT_C_PATH = str(Path(MLDSA_SOURCE_ROOT) / "ntt.c")
KNOWN_KEYS_C_PATH = str(Path(MLDSA_SOURCE_ROOT) / "known_keys.c")
