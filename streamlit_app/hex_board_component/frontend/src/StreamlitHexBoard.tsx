import { useCallback, useEffect, useState } from "react";
import {
  Streamlit,
  withStreamlitConnection,
  ComponentProps,
} from "streamlit-component-lib";
import HexBoardChart from "./HexBoardChart";
import type { BoardState } from "./types";

function StreamlitHexBoard({ args }: ComponentProps) {
  const boardState: BoardState | undefined = args["board_state"];

  const handleCellClick = useCallback((row: number, col: number) => {
    Streamlit.setComponentValue({ action: "cell_click", row, col });
  }, []);

  // Tell Streamlit our height whenever the board changes
  useEffect(() => {
    // Small delay so the chart has rendered and we can measure
    const timer = setTimeout(() => {
      Streamlit.setFrameHeight();
    }, 80);
    return () => clearTimeout(timer);
  }, [boardState]);

  if (!boardState) {
    return <div style={{ padding: 24, color: "#999" }}>Waiting for board data...</div>;
  }

  return <HexBoardChart boardState={boardState} onCellClick={handleCellClick} />;
}

export default withStreamlitConnection(StreamlitHexBoard);
