import { dirname, resolve } from "path";
import { fileURLToPath } from "url";
import { afterAll, expect, it, vi } from "vitest";

import { Optimizer } from "@/optimizer";
import type { OptimizerArgs } from "@/types";

import { getTestArgs, nothing } from "../test-helpers";

const mockLog = vi.spyOn(console, "log").mockImplementation(nothing);
const mockErr = vi.spyOn(console, "error").mockImplementation(nothing);

vi.useFakeTimers();
const resultpath = "";

// command to get the files
/*
$ for e in c json; do curl https://raw.githubusercontent.com/samuel-tian/fiat-crypto/master/fiat-$e/src/curve25519_solinas_64.$e > ./test/manual-bridge/modmul/curve25519_solinas.$e; done
// then, remove addcarryx, subborrowx and mulx from json,
// then, make mulmod non-static, non-inline
*/

const currentDir = dirname(fileURLToPath(import.meta.url));
const someCFilename = resolve(currentDir, "dettman", "secp256k1_dettman_64.c");
const someJsonFilename = resolve(currentDir, "dettman", "secp256k1_dettman_64.json");

it("optimise", () => {
  return new Promise((resolve, reject) => {
    const args: OptimizerArgs = getTestArgs("");
    args.bridge = "manual";
    args.curve = "";
    args.cFile = someCFilename;
    args.jsonFile = someJsonFilename;
    args.evals = 10;
    const opt = new Optimizer(args);
    console.warn({ someJsonFilename, someCFilename, resultDir: args.resultDir });

    try {
      opt.optimise().then((code) => {
        expect(code).toEqual(0);
        expect(mockErr).not.toHaveBeenCalled();
        resolve(0);
      });
      vi.runAllTimers();
    } catch (e) {
      mockErr.mockRestore();
      console.error(e);
      reject(e);
    }
  });
});

afterAll(() => {
  // readFileSync(resultpath);
  console.log(resultpath);
  // rm(resultpath, { recursive: true, force: true }, () => nothing);
  mockLog.mockRestore();
  mockErr.mockRestore();
  vi.useRealTimers();
});
