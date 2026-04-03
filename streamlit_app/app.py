"""
Random-Turn Hex — Streamlit App
Interactive hex game with Monte Carlo optimal strategy visualisation.
"""

from __future__ import annotations

import streamlit as st

from hex_engine import BoardTopology, Coord, HexBoard, Player
from hex_board_component import hex_board

st.set_page_config(
    page_title="Random-Turn Hex",
    page_icon="\u2b21",
    layout="wide",
    initial_sidebar_state="expanded",
)

# ── CSS ──────────────────────────────────────────────────────────────────────
st.markdown(
    """
<style>
    .main .block-container { padding-top: 1rem; max-width: 1200px; }
    .stSidebar .block-container { padding-top: 1rem; }
    div[data-testid="stSidebar"] { min-width: 320px; }
    .stat-card {
        background: linear-gradient(135deg, #1a1a2e, #16213e);
        border-radius: 12px; padding: 16px; margin: 4px 0;
        color: white; border: 1px solid #0f3460;
    }
    .stat-card h4 { margin: 0 0 4px 0; font-size: 13px; color: #8ecae6; }
    .stat-card .value { font-size: 24px; font-weight: 700; }
    .stat-red   { color: #e63946; }
    .stat-black { color: #adb5bd; }
    .stat-gold  { color: #f9c74f; }
    .move-pill {
        display: inline-block; padding: 2px 10px;
        border-radius: 12px; margin: 2px; font-size: 12px; font-weight: 600;
    }
    .move-red   { background: #e63946; color: white; }
    .move-black { background: #2b2d42; color: white; }
    .header-text {
        font-size: 28px; font-weight: 800;
        background: linear-gradient(135deg, #e63946, #2b2d42);
        -webkit-background-clip: text; -webkit-text-fill-color: transparent;
        margin-bottom: 0;
    }
    .sub-header { font-size: 13px; color: #666; margin-top: -8px; margin-bottom: 16px; }
</style>
""",
    unsafe_allow_html=True,
)

# ── Session defaults ─────────────────────────────────────────────────────────
_DEFAULTS: dict = dict(board=None, current_player=Player.RED, move_count=0, auto_compute=True, last_click=None)
for k, v in _DEFAULTS.items():
    st.session_state.setdefault(k, v)

# ── Sidebar ──────────────────────────────────────────────────────────────────
with st.sidebar:
    st.markdown('<p class="header-text">Random-Turn Hex</p>', unsafe_allow_html=True)
    st.markdown('<p class="sub-header">Monte Carlo strategy visualisation</p>', unsafe_allow_html=True)
    st.divider()

    st.subheader("Board Setup")
    board_size = st.slider("Board size", 3, 14, 7, help="Larger boards are slower to compute")
    topo_label = st.selectbox("Board topology", [t.label for t in BoardTopology])
    topology = next(t for t in BoardTopology if t.label == topo_label)

    st.divider()
    st.subheader("Strategy Engine")
    mc_iters = st.slider("Monte Carlo iterations", 500, 20_000, 3000, step=500)
    auto_compute = st.toggle("Auto-compute best move", value=True)
    st.session_state.auto_compute = auto_compute

    st.divider()
    st.subheader("Game Mode")
    game_mode = st.radio("Play mode", [
        "Interactive (Human vs Human)",
        "Human vs AI",
        "AI vs AI (Watch)",
        "Random Fill + Analyse",
    ])
    human_player = Player.RED
    if game_mode == "Human vs AI":
        human_label = st.radio("Play as", ["Red (top-bottom)", "Black (left-right)"])
        human_player = Player.RED if "Red" in human_label else Player.BLACK

    st.divider()
    st.subheader("Actions")
    c1, c2 = st.columns(2)
    new_game = c1.button("New Game", use_container_width=True, type="primary")
    compute_btn = c2.button("Compute Move", use_container_width=True)

    fill_btn = False
    fill_prob = 0.5
    if "Random Fill" in game_mode:
        fill_prob = st.slider("Fill probability", 0.0, 1.0, 0.5, 0.05)
        fill_btn = st.button("Random Fill Board", use_container_width=True)


# ── Helpers ──────────────────────────────────────────────────────────────────

def _new_game() -> None:
    st.session_state.board = HexBoard(board_size, topology)
    st.session_state.current_player = Player.RED
    st.session_state.move_count = 0
    st.session_state.last_click = None


def _place(coord: Coord, player: Player) -> bool:
    board: HexBoard = st.session_state.board
    if board.place(coord, player):
        st.session_state.move_count = board.move_count
        st.session_state.current_player = player.opponent
        return True
    return False


def _compute() -> Coord | None:
    board: HexBoard = st.session_state.board
    if board.is_game_over:
        return None
    return board.compute_best_move(st.session_state.current_player, mc_iters)


# ── Action handlers ──────────────────────────────────────────────────────────

if new_game:
    _new_game()
if st.session_state.board is None:
    _new_game()

board: HexBoard = st.session_state.board

if fill_btn and "Random Fill" in game_mode:
    board.random_fill(fill_prob)

if compute_btn:
    with st.spinner("Computing optimal move..."):
        _compute()

# ── Stats row ────────────────────────────────────────────────────────────────

cols = st.columns(4)
cur: Player = st.session_state.current_player
with cols[0]:
    cls = "stat-red" if cur is Player.RED else "stat-black"
    st.markdown(f'<div class="stat-card"><h4>Current Turn</h4><div class="value {cls}">{cur.label}</div></div>', unsafe_allow_html=True)
with cols[1]:
    st.markdown(f'<div class="stat-card"><h4>Moves Played</h4><div class="value">{board.move_count}</div></div>', unsafe_allow_html=True)
with cols[2]:
    st.markdown(f'<div class="stat-card"><h4>Empty Cells</h4><div class="value">{len(board.empty_cells())}</div></div>', unsafe_allow_html=True)
with cols[3]:
    bm = f"({board.best_move.row}, {board.best_move.col})" if board.best_move else "\u2014"
    st.markdown(f'<div class="stat-card"><h4>Best Move</h4><div class="value stat-gold">{bm}</div></div>', unsafe_allow_html=True)

if board.is_game_over:
    st.success(f"**{board.winner.label} wins!** Game over in {board.move_count} moves.")

# ── Board component ──────────────────────────────────────────────────────────

click = hex_board(board.get_board_state(), key="hex_board")

_click_id = (click["row"], click["col"]) if click and click.get("action") == "cell_click" else None
_is_new_click = _click_id is not None and _click_id != st.session_state.last_click and not board.is_game_over

if _is_new_click:
    st.session_state.last_click = _click_id
    coord = Coord(_click_id[0], _click_id[1])

    if "AI vs AI" not in game_mode:
        if "Human vs AI" in game_mode:
            if st.session_state.current_player == human_player:
                if _place(coord, human_player):
                    if auto_compute and not board.is_game_over:
                        _compute()
                    if not board.is_game_over:
                        ai_move = _compute()
                        if ai_move:
                            _place(ai_move, human_player.opponent)
                            if auto_compute and not board.is_game_over:
                                _compute()
                    st.rerun()
        else:
            if _place(coord, st.session_state.current_player):
                if auto_compute and not board.is_game_over:
                    _compute()
                st.rerun()

# ── AI vs AI controls ────────────────────────────────────────────────────────

if "AI vs AI" in game_mode and not board.is_game_over:
    a1, a2 = st.columns(2)
    step_btn = a1.button("Step (1 move)", use_container_width=True)
    play_all = a2.button("Play full game", use_container_width=True)

    if step_btn:
        with st.spinner("AI thinking..."):
            best = _compute()
            if best:
                _place(best, st.session_state.current_player)
                if auto_compute and not board.is_game_over:
                    _compute()
        st.rerun()

    if play_all:
        total = len(board.empty_cells())
        bar = st.progress(0)
        step = 0
        while not board.is_game_over and board.empty_cells():
            best = _compute()
            if best:
                _place(best, st.session_state.current_player)
            step += 1
            bar.progress(min(step / max(total, 1), 1.0))
        bar.empty()
        st.rerun()

# ── Move history ─────────────────────────────────────────────────────────────

if board.history:
    with st.expander(f"Move History ({board.move_count} moves)", expanded=False):
        pills = "".join(
            f'<span class="move-pill move-{m.player.label.lower()}">'
            f"{i + 1}. {'R' if m.player is Player.RED else 'B'}({m.coord.row},{m.coord.col})</span> "
            for i, m in enumerate(board.history)
        )
        st.markdown(pills, unsafe_allow_html=True)

# ── Sidebar footer ───────────────────────────────────────────────────────────

with st.sidebar:
    st.divider()
    st.caption("**How it works**")
    st.caption(
        "The engine runs Monte Carlo simulations filling empty cells randomly, "
        "then finds articulation points \u2014 cells whose ownership decides the game. "
        "The cell most frequently identified as an articulation point across all "
        "simulations is the recommended move."
    )
    st.caption(
        "**Board colours**: Red connects top\u2194bottom. Black connects left\u2194right. "
        "Probability heatmap shows cell importance (blue \u2192 green \u2192 gold)."
    )
