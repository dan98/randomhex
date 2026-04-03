import { useEffect, useRef, useMemo } from "react";
import * as echarts from "echarts/core";
import { CustomChart } from "echarts/charts";
import {
  TooltipComponent,
  GraphicComponent,
  GridComponent,
} from "echarts/components";
import { CanvasRenderer } from "echarts/renderers";
import type { BoardState, CellData } from "./types";
import {
  hexVertices,
  hexCenter,
  hexCorner,
  fitHexRadius,
  starPoints,
} from "./hex-geometry";
import { PAL, probColor } from "./palette";

echarts.use([
  CustomChart,
  TooltipComponent,
  GraphicComponent,
  GridComponent,
  CanvasRenderer,
]);

// ── Props ───────────────────────────────────────────────────────────────────

interface Props {
  boardState: BoardState;
  onCellClick: (row: number, col: number) => void;
}

// ── Helpers ─────────────────────────────────────────────────────────────────

const PADDING = 44;

function cellFill(d: CellData): string {
  if (d.state === "disabled") return PAL.disabled;
  if (d.state === "red") return PAL.red;
  if (d.state === "black") return PAL.black;
  return d.prob > 0.01 ? probColor(d.prob) : PAL.empty;
}

function buildBorderGraphics(
  n: number,
  r: number,
  px: number,
  py: number,
): any[] {
  const rr = r * 0.96;
  const t = r * 0.28; // thickness of edge strips

  function corner(row: number, col: number, idx: number): [number, number] {
    const [cx, cy] = hexCenter(row, col, r);
    const angle = Math.PI / 6 + (idx * Math.PI) / 3;
    return [cx + px + rr * Math.cos(angle), cy + py + rr * Math.sin(angle)];
  }

  // Push a point outward from the board edge by thickness t
  function pushOut(pt: [number, number], dx: number, dy: number): [number, number] {
    const len = Math.sqrt(dx * dx + dy * dy) || 1;
    return [pt[0] + (dx / len) * t, pt[1] + (dy / len) * t];
  }

  const elements: any[] = [];

  const edgeFillStyle = (color: string) => ({
    fill: color,
    opacity: 0.35,
  });
  const edgeStrokeStyle = (color: string) => ({
    stroke: color,
    lineWidth: 3,
    lineCap: "round" as const,
    lineJoin: "round" as const,
  });

  // For each edge cell, draw a filled trapezoid strip on the outside.
  // TOP edge (Red): for each cell in row 0, the top two edges are c3→c4 and c4→c5.
  // We draw a filled strip from the edge outward.
  for (let c = 0; c < n; c++) {
    const c3 = corner(0, c, 3);
    const c4 = corner(0, c, 4);
    const c5 = corner(0, c, 5);
    // Outward = upward (negative y)
    const o3 = pushOut(c3, 0, -1);
    const o4 = pushOut(c4, 0, -1);
    const o5 = pushOut(c5, 0, -1);
    elements.push({
      type: "polygon",
      shape: { points: [c3, c4, c5, o5, o4, o3] },
      style: edgeFillStyle(PAL.red),
      z: 1,
      silent: true,
    });
  }

  // BOTTOM edge (Red): last row, edges c2→c1 and c1→c0
  for (let c = 0; c < n; c++) {
    const c2 = corner(n - 1, c, 2);
    const c1 = corner(n - 1, c, 1);
    const c0 = corner(n - 1, c, 0);
    const o2 = pushOut(c2, 0, 1);
    const o1 = pushOut(c1, 0, 1);
    const o0 = pushOut(c0, 0, 1);
    elements.push({
      type: "polygon",
      shape: { points: [c2, c1, c0, o0, o1, o2] },
      style: edgeFillStyle(PAL.red),
      z: 1,
      silent: true,
    });
  }

  // LEFT edge (Black): col 0, edges c3→c2 per row, with linking segments c2→c3(next)
  for (let row = 0; row < n; row++) {
    const c3 = corner(row, 0, 3);
    const c2 = corner(row, 0, 2);
    // Outward = to the left (perpendicular to the edge)
    const mid: [number, number] = [(c3[0] + c2[0]) / 2, (c3[1] + c2[1]) / 2];
    const [cx, cy] = hexCenter(row, 0, r);
    const dx = mid[0] - (cx + px);
    const dy = mid[1] - (cy + py);
    const o3 = pushOut(c3, dx, dy);
    const o2 = pushOut(c2, dx, dy);
    elements.push({
      type: "polygon",
      shape: { points: [c3, c2, o2, o3] },
      style: edgeFillStyle(PAL.black),
      z: 1,
      silent: true,
    });
    // Linking segment between rows
    if (row < n - 1) {
      const nc3 = corner(row + 1, 0, 3);
      const midLink: [number, number] = [(c2[0] + nc3[0]) / 2, (c2[1] + nc3[1]) / 2];
      const dxL = midLink[0] - (cx + px);
      const dyL = midLink[1] - (cy + py);
      const oc2 = pushOut(c2, dxL, dyL);
      const onc3 = pushOut(nc3, dxL, dyL);
      elements.push({
        type: "polygon",
        shape: { points: [c2, nc3, onc3, oc2] },
        style: edgeFillStyle(PAL.black),
        z: 1,
        silent: true,
      });
    }
  }

  // RIGHT edge (Black): last col, edges c5→c0 per row, with linking segments
  for (let row = 0; row < n; row++) {
    const c5 = corner(row, n - 1, 5);
    const c0 = corner(row, n - 1, 0);
    const mid: [number, number] = [(c5[0] + c0[0]) / 2, (c5[1] + c0[1]) / 2];
    const [cx, cy] = hexCenter(row, n - 1, r);
    const dx = mid[0] - (cx + px);
    const dy = mid[1] - (cy + py);
    const o5 = pushOut(c5, dx, dy);
    const o0 = pushOut(c0, dx, dy);
    elements.push({
      type: "polygon",
      shape: { points: [c5, c0, o0, o5] },
      style: edgeFillStyle(PAL.black),
      z: 1,
      silent: true,
    });
    if (row < n - 1) {
      const nc5 = corner(row + 1, n - 1, 5);
      const midLink: [number, number] = [(c0[0] + nc5[0]) / 2, (c0[1] + nc5[1]) / 2];
      const dxL = midLink[0] - (cx + px);
      const dyL = midLink[1] - (cy + py);
      const oc0 = pushOut(c0, dxL, dyL);
      const onc5 = pushOut(nc5, dxL, dyL);
      elements.push({
        type: "polygon",
        shape: { points: [c0, nc5, onc5, oc0] },
        style: edgeFillStyle(PAL.black),
        z: 1,
        silent: true,
      });
    }
  }

  // Stroke lines on top of the fills for crisp edges
  // Top
  const topPts: [number, number][] = [];
  for (let c = 0; c < n; c++) topPts.push(corner(0, c, 3), corner(0, c, 4));
  topPts.push(corner(0, n - 1, 5));
  elements.push({ type: "polyline", shape: { points: topPts }, style: edgeStrokeStyle(PAL.red), z: 10, silent: true });

  // Bottom
  const botPts: [number, number][] = [];
  for (let c = 0; c < n; c++) botPts.push(corner(n - 1, c, 2), corner(n - 1, c, 1));
  botPts.push(corner(n - 1, n - 1, 0));
  elements.push({ type: "polyline", shape: { points: botPts }, style: edgeStrokeStyle(PAL.red), z: 10, silent: true });

  // Left
  const leftPts: [number, number][] = [corner(0, 0, 4)];
  for (let row = 0; row < n; row++) leftPts.push(corner(row, 0, 3), corner(row, 0, 2));
  leftPts.push(corner(n - 1, 0, 1));
  elements.push({ type: "polyline", shape: { points: leftPts }, style: edgeStrokeStyle(PAL.black), z: 10, silent: true });

  // Right
  const rightPts: [number, number][] = [];
  for (let row = 0; row < n; row++) rightPts.push(corner(row, n - 1, 5), corner(row, n - 1, 0));
  rightPts.push(corner(n - 1, n - 1, 1));
  elements.push({ type: "polyline", shape: { points: rightPts }, style: edgeStrokeStyle(PAL.black), z: 10, silent: true });

  return elements;
}

// ── Component ───────────────────────────────────────────────────────────────

export default function HexBoardChart({ boardState, onCellClick }: Props) {
  const containerRef = useRef<HTMLDivElement>(null);
  const chartRef = useRef<echarts.ECharts | null>(null);
  const onCellClickRef = useRef(onCellClick);
  onCellClickRef.current = onCellClick;

  // Build ECharts option from board state
  const option = useMemo(() => {
    const { n, cells } = boardState;
    const cw = containerRef.current?.clientWidth ?? 700;
    const hexR = fitHexRadius(n, cw, 9999, PADDING);
    const w = Math.sqrt(3) * hexR;
    const h = 2 * hexR;
    const boardW = w * n + w * (n - 1) * 0.5;
    const boardH = h * 0.75 * (n - 1) + h;
    const px = (cw - boardW) / 2;
    const py = PADDING;
    const chartH = boardH + py * 2;

    // Custom series data
    const hexData = cells.map((d) => {
      const [cx, cy] = hexCenter(d.row, d.col, hexR);
      return {
        value: [cx + px, cy + py, d.prob],
        _state: d.state,
        _prob: d.prob,
        _best: d.is_best,
        _row: d.row,
        _col: d.col,
      };
    });

    const borders = buildBorderGraphics(n, hexR, px, py);

    return {
      _chartH: chartH,
      _hexR: hexR,
      _px: px,
      _py: py,
      _cw: cw,
      option: {
        animation: true,
        animationDuration: 450,
        animationDurationUpdate: 550,
        animationEasingUpdate: "cubicInOut",
        tooltip: {
          trigger: "item",
          backgroundColor: "rgba(15,15,28,0.94)",
          borderColor: "rgba(255,255,255,0.08)",
          borderWidth: 1,
          padding: [10, 14],
          textStyle: {
            color: "#eee",
            fontSize: 13,
            fontFamily: "Inter, system-ui, sans-serif",
          },
          formatter: (params: any) => {
            const d = params.data;
            if (!d || d._state === undefined) return "";
            const labels: Record<string, string> = {
              empty: "Empty",
              red: "Red",
              black: "Black",
              disabled: "Disabled",
            };
            const colors: Record<string, string> = {
              red: PAL.red,
              black: PAL.black,
              empty: "#aaa",
              disabled: "#888",
            };
            let html = `<div style="margin-bottom:4px"><b style="color:${colors[d._state]}">${labels[d._state]}</b></div>`;
            html += `<div style="font-size:11px;color:#888">Cell (${d._row}, ${d._col})</div>`;
            if (d._state === "empty" && d._prob > 0.001) {
              html += `<div style="margin-top:6px;font-size:15px;font-weight:700;color:${probColor(d._prob)}">${(d._prob * 100).toFixed(1)}%</div>`;
              html += `<div style="font-size:10px;color:#666">articulation importance</div>`;
            }
            if (d._best) {
              html += `<div style="margin-top:5px;color:${PAL.bestGold};font-weight:700;font-size:12px">&#9733; Optimal move</div>`;
            }
            return html;
          },
        },
        xAxis: { show: false, min: 0, max: cw },
        yAxis: { show: false, min: 0, max: chartH },
        graphic: borders,
        series: [
          {
            id: "hexgrid",
            name: "hexgrid",
            type: "custom",
            coordinateSystem: "cartesian2d",
            data: hexData,
            z: 2,
            renderItem: (_params: any, api: any) => {
              const idx = _params.dataIndex;
              const d = hexData[idx];
              if (!d) return { type: "group", children: [] };
              const cx = api.value(0);
              const cy = api.value(1);
              const r = hexR * 0.96;
              const verts = hexVertices(cx, cy, r);
              const fill = cellFill(cells[idx]);
              const children: any[] = [];

              // Hex polygon
              children.push({
                type: "polygon",
                shape: { points: verts },
                style: {
                  fill,
                  stroke:
                    d._state === "disabled" ? PAL.borderLight : PAL.border,
                  lineWidth: d._state === "disabled" ? 0.5 : 1,
                },
                emphasis:
                  d._state === "empty"
                    ? {
                        style: {
                          fill:
                            d._prob > 0.01
                              ? probColor(Math.min(1, d._prob * 1.35))
                              : PAL.emptyHover,
                          shadowBlur: 16,
                          shadowColor: "rgba(0,0,0,0.28)",
                        },
                      }
                    : undefined,
                transition: ["style"],
              });

              // Specular highlight on placed pieces
              if (d._state === "red" || d._state === "black") {
                children.push({
                  type: "circle",
                  shape: {
                    cx: cx - r * 0.16,
                    cy: cy - r * 0.16,
                    r: r * 0.5,
                  },
                  style: {
                    fill: {
                      type: "radial",
                      x: 0.38,
                      y: 0.38,
                      r: 0.65,
                      colorStops: [
                        {
                          offset: 0,
                          color:
                            d._state === "red"
                              ? "rgba(255,180,185,0.5)"
                              : "rgba(150,155,195,0.4)",
                        },
                        { offset: 1, color: "rgba(0,0,0,0)" },
                      ],
                    },
                  },
                  silent: true,
                });
              }

              // Probability label
              if (d._state === "empty" && d._prob > 0.04 && hexR > 14) {
                children.push({
                  type: "text",
                  style: {
                    text: `${(d._prob * 100).toFixed(0)}%`,
                    x: cx,
                    y: d._best ? cy - r * 0.18 : cy,
                    fill: d._prob > 0.45 ? "#fff" : "#3a3a3a",
                    fontSize: Math.max(9, hexR * 0.3),
                    fontWeight: 700,
                    fontFamily: "Inter, system-ui, sans-serif",
                    align: "center",
                    verticalAlign: "middle",
                  },
                  silent: true,
                  transition: ["style"],
                });
              }

              // Best-move star
              if (d._best && d._state === "empty") {
                const sR = r * 0.2;
                const sY =
                  d._prob > 0.04 && hexR > 14 ? cy + r * 0.22 : cy;
                children.push({
                  type: "polygon",
                  shape: { points: starPoints(cx, sY, sR) },
                  style: {
                    fill: PAL.bestGold,
                    stroke: PAL.bestGlow,
                    lineWidth: 1.5,
                    opacity: 0.92,
                  },
                  silent: true,
                });
              }

              return { type: "group", children };
            },
          },
        ],
      } as echarts.EChartsCoreOption,
    };
  }, [boardState, containerRef.current?.clientWidth]);

  // Initialise chart
  useEffect(() => {
    if (!containerRef.current) return;
    const chart = echarts.init(containerRef.current, undefined, {
      renderer: "canvas",
    });
    chartRef.current = chart;

    chart.on("click", (params: any) => {
      const d = params.data;
      if (d && d._state === "empty") {
        onCellClickRef.current(d._row, d._col);
      }
    });

    return () => {
      chart.dispose();
      chartRef.current = null;
    };
  }, []);

  // Update chart on data change
  useEffect(() => {
    const chart = chartRef.current;
    if (!chart || !containerRef.current) return;

    const h = option._chartH;
    containerRef.current.style.height = `${h}px`;
    chart.resize();
    chart.setOption(option.option, { notMerge: true });
  }, [option]);

  // Resize handler
  useEffect(() => {
    const chart = chartRef.current;
    if (!chart || !containerRef.current) return;

    const ro = new ResizeObserver(() => {
      chart.resize();
      // Recompute layout on width change
      const h = option._chartH;
      if (containerRef.current) {
        containerRef.current.style.height = `${h}px`;
      }
      chart.setOption(option.option, { notMerge: true });
    });
    ro.observe(containerRef.current);
    return () => ro.disconnect();
  }, [option]);

  return (
    <div
      ref={containerRef}
      style={{ width: "100%", minHeight: 200, cursor: "pointer" }}
    />
  );
}
