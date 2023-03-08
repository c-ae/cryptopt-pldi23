import { getScalarsAndImmMappedAsConstArg } from "../helpers";
import type { SSA } from "../raw.type";
import type { Intermediate } from "./intermediate.type";

export function transformAnd(input: SSA): Intermediate {
  if (input.operation !== "and") {
    throw new Error("unsupported operation while transformAnd.");
  }
  let datatype: Intermediate["datatype"] = input.datatype;

  if (["i128", "i64"].includes(input.datatype)) {
    datatype = datatype.replaceAll("i", "u") as "u128" | "u64";
  }
  const args = getScalarsAndImmMappedAsConstArg(input.arguments);

  return {
    name: input.name,
    datatype,
    operation: "&",
    arguments: args,
  };
}
