import { DECISION_IDENTIFIER } from "@/enums";

export const DI_ABBRV = {
  [DECISION_IDENTIFIER.DI_CHOOSE_ARG]: "AR",
  [DECISION_IDENTIFIER.DI_HANDLE_FLAGS_KK]: "KK",
  [DECISION_IDENTIFIER.DI_FLAG]: "FL",
  [DECISION_IDENTIFIER.DI_INSTRUCTION_AND]: "B&",
  [DECISION_IDENTIFIER.DI_CHOOSE_IMM]: "IM",
  [DECISION_IDENTIFIER.DI_MULTIPLICATION_IMM]: "MU",
  [DECISION_IDENTIFIER.DI_SPILL_LOCATION]: "SL",
} as { [c in DECISION_IDENTIFIER]: string };
