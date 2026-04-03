/** Colour palette and helpers. */

export const PAL = {
  empty: "#ede8df",
  emptyHover: "#ddd6c8",
  disabled: "#d5d0c8",
  red: "#e63946",
  redLight: "#ff8a93",
  redDark: "#a82835",
  black: "#2b2d42",
  blackLight: "#6c6f8a",
  blackDark: "#1a1b2e",
  border: "#403d39",
  borderLight: "#bbb5a9",
  bestGold: "#f9c74f",
  bestGlow: "#ffe08a",
} as const;

// 4-stop probability colour ramp
const RAMP: [number, [number, number, number]][] = [
  [0.0, [232, 224, 223]],
  [0.25, [17, 138, 178]],
  [0.55, [6, 214, 160]],
  [1.0, [249, 199, 79]],
];

function lerp3(
  a: [number, number, number],
  b: [number, number, number],
  t: number,
): string {
  return `rgb(${Math.round(a[0] + (b[0] - a[0]) * t)},${Math.round(a[1] + (b[1] - a[1]) * t)},${Math.round(a[2] + (b[2] - a[2]) * t)})`;
}

export function probColor(p: number): string {
  if (p <= 0.01) return PAL.empty;
  for (let i = 1; i < RAMP.length; i++) {
    if (p <= RAMP[i][0]) {
      const t = (p - RAMP[i - 1][0]) / (RAMP[i][0] - RAMP[i - 1][0]);
      return lerp3(RAMP[i - 1][1], RAMP[i][1], t);
    }
  }
  return lerp3(RAMP[RAMP.length - 2][1], RAMP[RAMP.length - 1][1], 1);
}
