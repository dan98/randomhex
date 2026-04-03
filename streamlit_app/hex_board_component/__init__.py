"""Streamlit custom component — interactive Hex board (React + ECharts)."""

from __future__ import annotations

from pathlib import Path
from typing import Any

import streamlit.components.v1 as components

_BUILD_DIR = Path(__file__).parent / "frontend" / "build"
_component_func = components.declare_component("hex_board", path=str(_BUILD_DIR))


def hex_board(board_state: dict[str, Any], key: str | None = None) -> dict[str, Any] | None:
    """
    Render an interactive hex board.

    Parameters
    ----------
    board_state:
        Board state dict from ``HexBoard.get_board_state()``.
    key:
        Optional Streamlit component key for identity.

    Returns
    -------
    Click event payload ``{"action": "cell_click", "row": int, "col": int}``
    or *None* if no interaction yet.
    """
    return _component_func(board_state=board_state, key=key, default=None)
