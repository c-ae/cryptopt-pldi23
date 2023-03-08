import type { CryptOpt } from "@/types";

export type Intermediate = Pick<CryptOpt.DynArgument, "name" | "datatype" | "operation" | "arguments">;
