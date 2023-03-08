import { getArguments } from "../helpers";
import type { SSA } from "../raw.type";
import type { Intermediate } from "./intermediate.type";

export function transformAdd(input: SSA): Intermediate {
  if (input.operation !== "add") {
    throw new Error("unsupported operation while transform add.");
  }
  if (!["i128", "i64"].includes(input.datatype)) {
    throw new Error("unsupported datatype while transform add.");
  }

  const { scalars } = getArguments(input.arguments);

  return {
    name: input.name,
    datatype: input.datatype == "i128" ? "u128" : "u64",
    operation: "+",
    arguments: scalars.map(({ id }) => id),
  };
}
