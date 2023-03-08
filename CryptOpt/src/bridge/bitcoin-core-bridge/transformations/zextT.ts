import { getArguments } from "../helpers";
import type { SSA } from "../raw.type";
import type { Intermediate } from "./intermediate.type";

export function transformZext(input: SSA): Intermediate {
  if (input.operation !== "zext") {
    throw new Error("unsupported operation while transform zext.");
  }
  const { scalars, casts } = getArguments(input.arguments);

  let outType: Intermediate["datatype"];
  if (casts[0].type === "i128") {
    outType = "u128";
  } else if (casts[0].type === "i64") {
    outType = "u64";
  } else {
    throw new Error(`I am Afraid. I cannot zext to anything but u64/u128.`);
  }
  const args = scalars.map(({ id }) => id);
  // we dont really care, what the input is.
  // in the graph, it does not matter
  // while processing, we need to check whaat it is, either call RA.zext (to i64->i128) or movzx (for i1-> i64/i128)
  return {
    name: input.name,
    datatype: outType,
    operation: "zext",
    arguments: args,
  };
}
