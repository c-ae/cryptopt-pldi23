import { getArguments } from "../helpers";
import type { SSA } from "../raw.type";
import type { Intermediate } from "./intermediate.type";

export function transformOr(input: SSA): Intermediate {
  if (input.operation !== "or") {
    throw new Error("unsupported operation while transformOr.");
  }
  const datatype: Intermediate["datatype"] = input.datatype === "i64" ? "u64" : input.datatype;
  const { scalars } = getArguments(input.arguments);

  return {
    name: input.name,
    datatype,
    operation: "|",
    arguments: scalars.map(({ id }) => id),
  };
}
