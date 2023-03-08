import { defaults } from "lodash-es";
import { dirname, resolve } from "path";
import { fileURLToPath } from "url";

export const env = defaults(process.env, {
  CC: "gcc",
  CFLAGS: "-march=native -mtune=native -O3",
});

const me = fileURLToPath(import.meta.url);

// for this to work however, one must have executed `make build` at least once.
export const datadir =
  process.env.VITEST == "true"
    ? // in test, we are in './src/helper/env.ts'
      resolve(dirname(me), "..", "..", "dist", "data")
    : // in prod, me is './dist/optimizer.helper.class-hash.js'
      resolve(dirname(me), "data");
