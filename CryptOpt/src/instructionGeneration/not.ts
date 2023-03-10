import { AllocationFlags } from "@/enums";
import { RegisterAllocator } from "@/registerAllocator";
import type { asm, CryptOpt } from "@/types";

export function not(c: CryptOpt.StringOperation): asm[] {
  const ra = RegisterAllocator.getInstance();
  ra.initNewInstruction(c);
  const [inVarname] = c.arguments as string[];
  const allocation = ra.allocate({
    oReg: c.name,
    in: [inVarname],
    allocationFlags: AllocationFlags.DISALLOW_XMM | AllocationFlags.IN_0_AS_OUT_REGISTER,
  });

  return [...ra.pres, `not ${allocation.oReg[0]}; ${c.name[0]} <- not ${inVarname}`];
}
