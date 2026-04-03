/**
 * Hex grid geometry helpers (pointy-top orientation).
 */

const SQRT3 = Math.sqrt(3);
const PI_OVER_6 = Math.PI / 6;

/** Six corner points of a pointy-top hexagon centred at (cx, cy). */
export function hexVertices(
  cx: number,
  cy: number,
  r: number,
): [number, number][] {
  const pts: [number, number][] = [];
  for (let i = 0; i < 6; i++) {
    const angle = PI_OVER_6 + (i * Math.PI) / 3;
    pts.push([cx + r * Math.cos(angle), cy + r * Math.sin(angle)]);
  }
  return pts;
}

/** Pixel centre for a cell at (row, col) given hex radius. */
export function hexCenter(
  row: number,
  col: number,
  r: number,
): [number, number] {
  const w = SQRT3 * r;
  const h = 2 * r;
  return [w * (col + 0.5) + row * w * 0.5, row * h * 0.75 + h * 0.5];
}

/** A single corner of a hex at (row, col), identified by corner index 0..5. */
export function hexCorner(
  row: number,
  col: number,
  r: number,
  cornerIdx: number,
): [number, number] {
  const [cx, cy] = hexCenter(row, col, r);
  const angle = PI_OVER_6 + (cornerIdx * Math.PI) / 3;
  return [cx + r * Math.cos(angle), cy + r * Math.sin(angle)];
}

/**
 * Compute hex radius that fits an n×n board inside (width × height),
 * with the given padding.
 */
export function fitHexRadius(
  n: number,
  width: number,
  height: number,
  padding: number,
): number {
  const availW = width - padding * 2;
  const availH = height - padding * 2;
  const colSpan = n * 1.5 + 0.5;
  const rowSpan = n + 0.5;
  const rByW = availW / (colSpan * SQRT3);
  const rByH = availH / (rowSpan * 2);
  return Math.min(rByW, rByH);
}

/** 5-pointed star vertices. */
export function starPoints(
  cx: number,
  cy: number,
  r: number,
  n: number = 5,
): [number, number][] {
  const pts: [number, number][] = [];
  for (let i = 0; i < n * 2; i++) {
    const angle = -Math.PI / 2 + (i * Math.PI) / n;
    const rad = i % 2 === 0 ? r : r * 0.42;
    pts.push([cx + rad * Math.cos(angle), cy + rad * Math.sin(angle)]);
  }
  return pts;
}
