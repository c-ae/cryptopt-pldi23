import { getScalarsAndImmMappedAsConstArg } from "../helpers";
import type { SSA } from "../raw.type";
import type { Intermediate } from "./intermediate.type";

export function transformMul(input: SSA): Intermediate {
  if (input.operation !== "mul") {
    throw new Error("unsupported operation while transform mul.");
  }
  if (!["i128", "i64"].includes(input.datatype)) {
    throw new Error("unsupported datatype while transform mul.");
  }

  const args = getScalarsAndImmMappedAsConstArg(input.arguments);

  return {
    name: input.name,
    datatype: input.datatype == "i128" ? "u128" : "u64",
    operation: "mulx",
    arguments: args,
  };
}
