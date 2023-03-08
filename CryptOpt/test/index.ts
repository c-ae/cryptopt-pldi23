import type { SpyInstance } from "vitest";
import { afterAll, beforeAll, describe, expect, it, vi } from "vitest";

import { Optimizer } from "@/optimizer";

import { getTestArgs } from "./test-helpers";

describe("full tests fiat", () => {
  let mockLog: SpyInstance;
  let mockErr: SpyInstance;
  beforeAll(() => {
    const dofkall = (_msg: string) => {
      /*intentionally empty*/
    };
    mockLog = vi.spyOn(console, "log").mockImplementation(dofkall);
    mockErr = vi.spyOn(console, "error").mockImplementation(dofkall);
  });
  afterAll(() => {
    mockLog.mockRestore();
    mockErr.mockRestore();
  });
  it("shoud error", () => {
    expect(() => {
      throw new Error("n");
    }).toThrow();
  });
  const args = getTestArgs("curve25519-square.ts");

  it("should only throw on invalid curves.", () => {
    expect(() => {
      new Optimizer(args);
    }).not.toThrow();

    expect(() => {
      new Optimizer(Object.assign({}, args, { curve: "INVALIDCURVE", method: "square" }));
    }).toThrow(/Cannot destructure property '.*' of '.*' as it is undefined./);
  });

  afterAll(() => {
    vi.useRealTimers();
  });
});
