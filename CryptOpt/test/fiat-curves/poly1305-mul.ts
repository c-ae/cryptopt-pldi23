import { basename } from "path";
import { afterAll, expect, it, vi } from "vitest";

import { Optimizer } from "@/optimizer";

import { getTestArgs, nothing } from "../test-helpers";

const mockLog = vi.spyOn(console, "log").mockImplementation(nothing);
const mockErr = vi.spyOn(console, "error").mockImplementation(nothing);

vi.useFakeTimers();

it("optimise", () => {
  return new Promise((resolve, reject) => {
    const filename = basename(import.meta.url);
    const args = getTestArgs(filename);
    const opt = new Optimizer(args);

    try {
      expect(() =>
        opt.optimise().then((code) => {
          expect(code).toEqual(0);
          expect(mockErr).not.toHaveBeenCalled();
          resolve(0);
        }),
      ).not.toThrow();
      vi.runAllTimers();
    } catch (e) {
      mockErr.mockRestore();
      console.error(e);
      reject(e);
    }
  });
});

afterAll(() => {
  mockLog.mockRestore();
  mockErr.mockRestore();
  vi.useRealTimers();
});
