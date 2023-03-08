import fs from "fs";
import { FiatBridge } from "./bridge/fiat-bridge";
main();

function main() {
  const [, , filename] = process.argv;
  const asmString = fs.readFileSync(filename).toString();
  const map = {
    fiat_curve25519_carry_mul: { curve: "curve25519", method: "mul" },
    fiat_curve25519_carry_square: { curve: "curve25519", method: "square" },
    fiat_p224_mul: { curve: "p224", method: "mul" },
    fiat_p224_square: { curve: "p224", method: "square" },
    fiat_p256_mul: { curve: "p256", method: "mul" },
    fiat_p256_square: { curve: "p256", method: "square" },
    fiat_p384_mul: { curve: "p384", method: "mul" },
    fiat_p384_square: { curve: "p384", method: "square" },
    fiat_p434_mul: { curve: "p434", method: "mul" },
    fiat_p434_square: { curve: "p434", method: "square" },
    fiat_p448_solinas_carry_mul: { curve: "p448_solinas", method: "mul" },
    fiat_p448_solinas_carry_square: { curve: "p448_solinas", method: "square" },
    fiat_p521_carry_mul: { curve: "p521", method: "mul" },
    fiat_p521_carry_square: { curve: "p521", method: "square" },
    fiat_poly1305_carry_mul: { curve: "poly1305", method: "mul" },
    fiat_poly1305_carry_square: { curve: "poly1305", method: "square" },
    fiat_secp256k1_mul: { curve: "secp256k1", method: "mul" },
    fiat_secp256k1_square: { curve: "secp256k1", method: "square" },
    fiat_secp256k1_dettman_mul: { curve: "secp256k1_dettman", method: "mul" },
  };
  const { method, curve } = map[getSymbol(asmString) as keyof typeof map];

  const command = FiatBridge.buildProofCommand(curve, method, filename);
  console.log(command);
}

function getSymbol(asmstring: string): string | never {
  const symbol = asmstring
    .split("\n")
    .find((e) => e.includes("GLOBAL"))
    ?.match(/\s*GLOBAL (?<symbol>.*)/)?.groups?.symbol;
  if (!symbol) {
    console.error("Cannot find any symbol in asmstring. Must match /\\s*GLOBAL (?<symbol>.*)/");
    process.exit(-1);
  }
  return symbol;
}
