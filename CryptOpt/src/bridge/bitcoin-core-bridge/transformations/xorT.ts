import { getScalarsAndImmMappedAsConstArg } from "../helpers";
import type { SSA } from "../raw.type";
import type { Intermediate } from "./intermediate.type";

export function transformXor(input: SSA): Intermediate {
  if (input.operation !== "xor") {
    throw new Error("unsupported operation while transformXOr.");
  }
  const datatype: Intermediate["datatype"] = input.datatype === "i64" ? "u64" : input.datatype;
  const args = getScalarsAndImmMappedAsConstArg(input.arguments);

  return {
    name: input.name,
    datatype,
    operation: "^",
    arguments: args,
  };
}
