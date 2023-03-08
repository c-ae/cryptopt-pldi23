import { readFileSync } from "fs";
import { dirname, resolve as pathResolve } from "path";
import { fileURLToPath } from "url";
import { afterAll, expect, it, vi } from "vitest";

import { Optimizer } from "@/optimizer";

import { getTestResultsPath, nothing } from "../test-helpers";

const mockLog = vi.spyOn(console, "log").mockImplementation(nothing);
const mockErr = vi.spyOn(console, "error").mockImplementation(nothing);

vi.useFakeTimers();

it("optimise", () => {
  return new Promise((resolve, reject) => {
    const dir = dirname(fileURLToPath(import.meta.url));
    const statefile = pathResolve(dir, "./seed0000000688561254.json");
    const args = JSON.parse(readFileSync(statefile).toString()).parsedArgs;
    args.resultDir = getTestResultsPath();
    args.readState = statefile;
    expect(args).toBeTruthy();
    const opt = new Optimizer(args);

    try {
      expect(() =>
        opt.optimise().then((code) => {
          expect(code).toEqual(0);
          resolve(0);
        }),
      ).not.toThrow();
      vi.runAllTimers();
    } catch (e) {
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
