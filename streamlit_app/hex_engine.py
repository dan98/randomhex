"""
hex_engine — Modern OOP hex game engine.

Ported from the C++ simulator. Provides board state management, connectivity
analysis via articulation-point detection, and Monte Carlo move generation.
"""

from __future__ import annotations

import math
import random
from collections import deque
from enum import IntEnum
from typing import Any

# ── Hex neighbour offsets (6 directions) ─────────────────────────────────────
_DX = (1, 0, -1, 0, -1, 1)
_DY = (0, 1, 0, -1, 1, -1)

# Internal sentinel for disabled / wall cells
_DISABLED = -2


# ── Public enums & value objects ─────────────────────────────────────────────

class Player(IntEnum):
    RED = 0    # connects top ↔ bottom
    BLACK = 1  # connects left ↔ right

    @property
    def opponent(self) -> Player:
        return Player(1 - self.value)

    @property
    def label(self) -> str:
        return self.name.capitalize()


class CellState(IntEnum):
    DISABLED = -2
    EMPTY = -1
    RED = 0
    BLACK = 1

    @property
    def label(self) -> str:
        return self.name.lower()

    @property
    def is_playable(self) -> bool:
        return self is not CellState.DISABLED


class BoardTopology(IntEnum):
    STANDARD = 0
    TRIANGLE = 1
    TRAPEZIUM = 2
    CENTER_DISABLED = 3

    @property
    def label(self) -> str:
        return {
            0: "Standard Hex",
            1: "Triangle",
            2: "Trapezium",
            3: "Center Disabled",
        }[self.value]


class Coord:
    """Immutable (row, col) in game-space (0-indexed)."""

    __slots__ = ("row", "col")

    def __init__(self, row: int, col: int) -> None:
        self.row = row
        self.col = col

    # ── Conversion to internal grid (padded by 2) ────────────────────────
    @property
    def _ix(self) -> int:
        return self.row + 2

    @property
    def _iy(self) -> int:
        return self.col + 2

    def __eq__(self, other: object) -> bool:
        if isinstance(other, Coord):
            return self.row == other.row and self.col == other.col
        return NotImplemented

    def __hash__(self) -> int:
        return hash((self.row, self.col))

    def __repr__(self) -> str:
        return f"Coord({self.row}, {self.col})"

    def to_dict(self) -> dict[str, int]:
        return {"row": self.row, "col": self.col}


class Move:
    """A single move record."""

    __slots__ = ("coord", "player", "probability")

    def __init__(self, coord: Coord, player: Player, probability: float = 0.0) -> None:
        self.coord = coord
        self.player = player
        self.probability = probability

    def to_dict(self) -> dict[str, Any]:
        return {
            "row": self.coord.row,
            "col": self.coord.col,
            "color": self.player.label.lower(),
            "probability": self.probability,
        }


# ── Internal grid (padded coordinate system) ────────────────────────────────

class _Grid:
    """
    2-D array with +2 boundary padding on each side.

    Game cell (r, c) maps to internal index (r+2, c+2).
    Boundary / wall cells hold ``_DISABLED``.
    """

    __slots__ = ("_size", "_data")

    def __init__(self, n: int, fill: Any = _DISABLED) -> None:
        self._size = n + 4
        self._data: list[list[Any]] = [[fill] * self._size for _ in range(self._size)]

    # fast internal access
    def iget(self, x: int, y: int) -> Any:
        return self._data[x][y]

    def iset(self, x: int, y: int, val: Any) -> None:
        self._data[x][y] = val

    # game-coord access
    def get(self, coord: Coord) -> Any:
        return self._data[coord._ix][coord._iy]

    def set(self, coord: Coord, val: Any) -> None:
        self._data[coord._ix][coord._iy] = val

    def copy_raw(self) -> list[list[Any]]:
        return [row[:] for row in self._data]

    def raw(self) -> list[list[Any]]:
        return self._data

    @property
    def padded_size(self) -> int:
        return self._size


# ── Topology initializers ────────────────────────────────────────────────────

class _TopologyFactory:
    """Creates the initial cell grid for each ``BoardTopology``."""

    @staticmethod
    def init(grid: _Grid, n: int, topo: BoardTopology) -> None:
        method = {
            BoardTopology.STANDARD: _TopologyFactory._standard,
            BoardTopology.TRIANGLE: _TopologyFactory._triangle,
            BoardTopology.TRAPEZIUM: _TopologyFactory._trapezium,
            BoardTopology.CENTER_DISABLED: _TopologyFactory._center_disabled,
        }[topo]
        method(grid, n)

    @staticmethod
    def _standard(grid: _Grid, n: int) -> None:
        for i in range(2, n + 2):
            for j in range(2, n + 2):
                grid.iset(i, j, CellState.EMPTY)

    @staticmethod
    def _triangle(grid: _Grid, n: int) -> None:
        for i in range(2, n + 2):
            for j in range(2, n + 2):
                if (i - 2) + (j - 2) >= n - 1:
                    grid.iset(i, j, CellState.EMPTY)

    @staticmethod
    def _trapezium(grid: _Grid, n: int) -> None:
        for i in range(2, n + 2):
            for j in range(2, n + 2):
                if (i - 2) + (j - 2) >= n - 1 and (i - 2) > 0:
                    grid.iset(i, j, CellState.EMPTY)

    @staticmethod
    def _center_disabled(grid: _Grid, n: int) -> None:
        _TopologyFactory._standard(grid, n)
        k = max(1, n // 3)
        offset = (n - k) // 2 + 2
        for i in range(offset, offset + k):
            for j in range(offset, offset + k):
                grid.iset(i, j, CellState.DISABLED)


# ── Connectivity analyser (articulation-point DFS) ───────────────────────────

class _ConnectivityAnalyser:
    """
    Find articulation points for a player on a given (temporary) colour grid.

    An articulation point is a cell whose removal disconnects the player's
    source boundary from their sink boundary.
    """

    def __init__(self, n: int) -> None:
        self._n = n

    def _in_bounds(self, x: int, y: int) -> bool:
        s = self._n + 4
        return 0 <= x < s and 0 <= y < s

    def find(self, raw_grid: list[list[int]], player: Player) -> set[tuple[int, int]]:
        n = self._n
        visited: dict[tuple[int, int], bool] = {}
        depth: dict[tuple[int, int], int] = {}
        low: dict[tuple[int, int], int] = {}
        art: set[tuple[int, int]] = set()

        source: set[tuple[int, int]] = set()
        sink: set[tuple[int, int]] = set()

        for i in range(2, n + 2):
            for j in range(2, n + 2):
                if raw_grid[i][j] != player.value:
                    continue
                if player is Player.RED:
                    if i == 2:
                        source.add((i, j))
                    if i == n + 1:
                        sink.add((i, j))
                else:
                    if j == 2:
                        source.add((i, j))
                    if j == n + 1:
                        sink.add((i, j))

        timer = [0]

        def dfs(u: tuple[int, int], par: tuple[int, int] | None) -> bool:
            visited[u] = True
            depth[u] = low[u] = timer[0]
            timer[0] += 1
            children = 0
            reaches = u in sink

            for k in range(6):
                nx, ny = u[0] + _DX[k], u[1] + _DY[k]
                v = (nx, ny)
                if not self._in_bounds(nx, ny) or raw_grid[nx][ny] != player.value:
                    continue
                if v not in visited:
                    children += 1
                    child_reaches = dfs(v, u)
                    reaches = reaches or child_reaches
                    low[u] = min(low[u], low[v])
                    if par is not None and low[v] >= depth[u] and child_reaches:
                        art.add(u)
                    if par is None and children > 1:
                        art.add(u)
                elif v != par:
                    low[u] = min(low[u], depth[v])

            return reaches

        for s in source:
            if s not in visited:
                dfs(s, None)

        return art


# ── Monte-Carlo strategy engine ──────────────────────────────────────────────

class StrategyEngine:
    """
    Estimates the optimal next move via Monte-Carlo articulation-point sampling.

    For each iteration the engine fills every empty cell randomly,
    detects articulation points for both players, and tallies which empty
    cells appear as bridges most often.
    """

    def __init__(self, board: HexBoard) -> None:
        self._board = board
        self._analyser = _ConnectivityAnalyser(board.size)

    def compute(self, player: Player, iterations: int = 5000) -> Coord | None:
        board = self._board
        n = board.size

        # Collect empty cells in internal coords
        empties: list[tuple[int, int]] = []
        for i in range(2, n + 2):
            for j in range(2, n + 2):
                if board._cells.iget(i, j) == CellState.EMPTY:
                    empties.append((i, j))

        if not empties:
            return None

        cnt: dict[tuple[int, int], float] = {c: 0.0 for c in empties}
        raw_base = board._cells.copy_raw()

        for _ in range(iterations):
            raw = [row[:] for row in raw_base]
            for x, y in empties:
                raw[x][y] = Player.RED if random.random() < 0.5 else Player.BLACK

            for p in (player, player.opponent):
                for pt in self._analyser.find(raw, p):
                    if pt in cnt:
                        cnt[pt] += 1

        # Normalise (L2)
        norm = math.sqrt(sum(v * v for v in cnt.values())) or 1.0
        for i in range(2, n + 2):
            for j in range(2, n + 2):
                board._probs.iset(i, j, cnt.get((i, j), 0.0) / norm)

        best_internal = max(cnt, key=cnt.get)
        best = Coord(best_internal[0] - 2, best_internal[1] - 2)
        board._best_move = best
        return best


# ── HexBoard ─────────────────────────────────────────────────────────────────

class HexBoard:
    """
    Complete game state for an *n* x *n* hex board.

    Separates concerns:
    * Grid storage       → ``_Grid``
    * Topology init      → ``_TopologyFactory``
    * Connectivity       → ``_ConnectivityAnalyser``
    * Strategy           → ``StrategyEngine``
    """

    def __init__(self, size: int, topology: BoardTopology = BoardTopology.STANDARD) -> None:
        if not 2 <= size <= 19:
            raise ValueError(f"Board size must be 2..19, got {size}")

        self._size = size
        self._topology = topology
        self._cells = _Grid(size, CellState.DISABLED)
        self._fixed = _Grid(size, False)
        self._probs = _Grid(size, 0.0)
        self._best_move: Coord | None = None
        self._winner: Player | None = None
        self._history: list[Move] = []

        _TopologyFactory.init(self._cells, size, topology)

    # ── Properties ───────────────────────────────────────────────────────

    @property
    def size(self) -> int:
        return self._size

    @property
    def topology(self) -> BoardTopology:
        return self._topology

    @property
    def best_move(self) -> Coord | None:
        return self._best_move

    @property
    def winner(self) -> Player | None:
        return self._winner

    @property
    def is_game_over(self) -> bool:
        return self._winner is not None

    @property
    def history(self) -> list[Move]:
        return list(self._history)

    @property
    def move_count(self) -> int:
        return len(self._history)

    # ── Cell access ──────────────────────────────────────────────────────

    def cell_at(self, coord: Coord) -> CellState:
        return CellState(self._cells.get(coord))

    def prob_at(self, coord: Coord) -> float:
        return self._probs.get(coord)

    def empty_cells(self) -> list[Coord]:
        cells: list[Coord] = []
        for r in range(self._size):
            for c in range(self._size):
                if self._cells.iget(r + 2, c + 2) == CellState.EMPTY:
                    cells.append(Coord(r, c))
        return cells

    # ── Mutations ────────────────────────────────────────────────────────

    def place(self, coord: Coord, player: Player) -> bool:
        """Place a stone. Returns *True* on success."""
        if self.is_game_over:
            return False
        if self._cells.get(coord) != CellState.EMPTY:
            return False
        if self._fixed.get(coord):
            return False

        self._cells.set(coord, CellState(player.value))
        self._fixed.set(coord, True)
        self._history.append(Move(coord, player, self._probs.get(coord)))
        self._check_winner()
        return True

    def random_fill(self, bias: float = 0.5) -> None:
        """Fill every empty cell randomly (RED with probability *bias*)."""
        for r in range(self._size):
            for c in range(self._size):
                ix, iy = r + 2, c + 2
                if self._cells.iget(ix, iy) == CellState.EMPTY:
                    self._cells.iset(
                        ix, iy,
                        CellState.RED if random.random() < bias else CellState.BLACK,
                    )
        self._check_winner()

    def compute_best_move(self, player: Player, iterations: int = 5000) -> Coord | None:
        """Run the Monte-Carlo strategy engine and return the best move."""
        engine = StrategyEngine(self)
        return engine.compute(player, iterations)

    # ── Winner detection (BFS) ───────────────────────────────────────────

    def _check_winner(self) -> None:
        for player in Player:
            if self._has_winning_path(player):
                self._winner = player
                return

    def _has_winning_path(self, player: Player) -> bool:
        n = self._size
        visited: set[tuple[int, int]] = set()
        queue: deque[tuple[int, int]] = deque()

        # Seed from source boundary
        for k in range(n):
            coord = Coord(0, k) if player is Player.RED else Coord(k, 0)
            if self.cell_at(coord) == CellState(player.value):
                pair = (coord.row, coord.col)
                queue.append(pair)
                visited.add(pair)

        while queue:
            r, c = queue.popleft()
            if player is Player.RED and r == n - 1:
                return True
            if player is Player.BLACK and c == n - 1:
                return True

            ix, iy = r + 2, c + 2
            for d in range(6):
                nr, nc = ix + _DX[d] - 2, iy + _DY[d] - 2
                if 0 <= nr < n and 0 <= nc < n and (nr, nc) not in visited:
                    if self._cells.iget(nr + 2, nc + 2) == player.value:
                        visited.add((nr, nc))
                        queue.append((nr, nc))
        return False

    # ── Serialisation ────────────────────────────────────────────────────

    def get_board_state(self) -> dict[str, Any]:
        """Full state dict consumed by the React component."""
        n = self._size
        cells: list[dict[str, Any]] = []
        for r in range(n):
            for c in range(n):
                coord = Coord(r, c)
                state = self.cell_at(coord)
                cells.append({
                    "row": r,
                    "col": c,
                    "state": state.label,
                    "prob": round(self.prob_at(coord), 6),
                    "is_best": self._best_move == coord if self._best_move else False,
                })
        return {
            "n": n,
            "cells": cells,
            "board_type": self._topology.value,
            "winner": self._winner.label.lower() if self._winner else None,
            "best_move": self._best_move.to_dict() if self._best_move else None,
            "move_history": [m.to_dict() for m in self._history],
        }

    def to_dict(self) -> dict[str, Any]:
        """Minimal serialisable snapshot for session persistence."""
        n = self._size
        return {
            "n": n,
            "topology": self._topology.value,
            "cells": self._cells.copy_raw(),
            "fixed": [[bool(self._fixed.iget(i, j)) for j in range(n + 4)] for i in range(n + 4)],
            "probs": self._probs.copy_raw(),
            "best_move": self._best_move.to_dict() if self._best_move else None,
            "winner": self._winner.value if self._winner is not None else None,
            "history": [
                {"row": m.coord.row, "col": m.coord.col,
                 "player": m.player.value, "probability": m.probability}
                for m in self._history
            ],
        }

    @classmethod
    def from_dict(cls, data: dict[str, Any]) -> HexBoard:
        """Reconstruct from a ``to_dict`` snapshot."""
        board = cls(data["n"], BoardTopology(data["topology"]))
        # Overwrite grids
        for i, row in enumerate(data["cells"]):
            for j, v in enumerate(row):
                board._cells.iset(i, j, v)
        for i, row in enumerate(data["fixed"]):
            for j, v in enumerate(row):
                board._fixed.iset(i, j, bool(v))
        for i, row in enumerate(data["probs"]):
            for j, v in enumerate(row):
                board._probs.iset(i, j, v)
        if data["best_move"]:
            board._best_move = Coord(data["best_move"]["row"], data["best_move"]["col"])
        board._winner = Player(data["winner"]) if data["winner"] is not None else None
        board._history = [
            Move(Coord(m["row"], m["col"]), Player(m["player"]), m["probability"])
            for m in data["history"]
        ]
        return board
