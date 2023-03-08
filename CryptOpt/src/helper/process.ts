import { Model } from "@/model";
import { CryptOpt } from "@/types";

import { cy, re } from "./constants";
import { generateResultFilename } from "./path";

export function registerExitHooks(args: Parameters<typeof generateResultFilename>[0]) {
  const [stateFileName] = generateResultFilename(args);

  process.on("exit", (exitcode: number) => {
    if (exitcode == 0) {
      process.stdout.write(`\nDone Success. ${cy}${new Date().toISOString()}${re}\n`);
    } else {
      process.stderr.write(`\nDone with code: ${exitcode} (statefile: ${stateFileName})\n`);
    }
    Model.persist(stateFileName, args as unknown as CryptOpt.StateFile["parsedArgs"]);
    process.stdout.write("exiting.\n");
    process.exit(exitcode);
  });

  process.on("SIGINT", (signal: "SIGINT") => {
    process.stdout.write(`\ncaught ${signal}`);
    process.exit(13);
  });

  process.on("SIGTERM", (signal: "SIGTERM") => {
    process.stdout.write(`\ncaught ${signal}`);
    process.exit(13);
  });
}
