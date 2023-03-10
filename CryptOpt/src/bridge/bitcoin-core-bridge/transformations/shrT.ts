import { getArguments, getScalarsAndImmMappedAsConstArg } from "../helpers";
import type { SSA } from "../raw.type";
import type { Intermediate } from "./intermediate.type";

export const transformAshr = shr;
export const transformLshr = shr;
function shr(input: SSA): Intermediate {
  if (!["lshr", "ashr"].includes(input.operation)) {
    throw new Error("unsupported operation while transform shift right.");
  }
  if (!["i128", "i64"].includes(input.datatype)) {
    throw new Error("unsupported datatype while transform shift right.");
  }

  const { scalars, imm } = getArguments(input.arguments);
  // special case, if its a i128>>64
  if (imm[0].imm == "64" && input.datatype == "i128") {
    return {
      name: input.name,
      datatype: "u64",
      operation: "limb",
      arguments: [scalars[0].id, "1"],
    };
  }
  const args = getScalarsAndImmMappedAsConstArg(input.arguments);
  return {
    name: input.name,
    datatype: input.datatype == "i128" ? "u128" : "u64",
    operation: input.operation == "lshr" ? ">>" : "sar",
    arguments: args,
  };
}
