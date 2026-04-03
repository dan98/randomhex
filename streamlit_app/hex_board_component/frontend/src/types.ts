export type CellState = "empty" | "red" | "black" | "disabled";

export interface CellData {
  row: number;
  col: number;
  state: CellState;
  prob: number;
  is_best: boolean;
}

export interface MoveRecord {
  row: number;
  col: number;
  color: "red" | "black";
  probability: number;
}

export interface BoardState {
  n: number;
  cells: CellData[];
  board_type: number;
  winner: "red" | "black" | null;
  best_move: { row: number; col: number } | null;
  move_history: MoveRecord[];
}
