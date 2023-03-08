import { existsSync, mkdirSync } from "fs";
import { resolve } from "path";

import Logger from "@/helper/Logger.class";
import type { OptimizerArgs } from "@/types";

import { padSeed } from "./lamdas";

export function generateResultFilename(
  {
    resultDir,
    bridge,
    seed,
    symbolname,
  }: Pick<OptimizerArgs, "resultDir" | "bridge" | "seed"> & {
    symbolname: string;
  },
  suff = [".json"],
): string[] {
  const path =
    resultDir && resultDir !== ""
      ? resolve(resultDir, bridge, symbolname)
      : resolve(`${process.cwd()}/results`, bridge, symbolname);

  if (!existsSync(path)) {
    Logger.log(`${path} does not exist. Trying to create it.`);
    try {
      mkdirSync(path, { recursive: true });
    } catch (e) {
      const msg = `${path} does not exist. And could not be created due to Error:${e}. Create that folder manually and re-run. Exiting.`;
      console.error(msg);
      process.exit(2);
    }
  }

  const padded = padSeed(seed);
  return suff.map((s) => resolve(path, `seed${padded}${s}`).toString());
}
