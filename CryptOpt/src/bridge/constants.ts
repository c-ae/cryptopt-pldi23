export const BRIDGES = ["fiat", "bitcoin-core", "manual"];

// currently used only in src/CountCycle
export const KNOWN_SYMBOLS: {
  [symbol: string]: { bridge: "fiat" | "bitcoin-core"; method: string; curve: string };
} = {
  // fiat curves
  fiat_curve25519_carry_mul: { bridge: "fiat", method: "mul", curve: "curve25519" },
  fiat_curve25519_carry_square: { bridge: "fiat", method: "square", curve: "curve25519" },
  fiat_curve25519_solinas_mul: { bridge: "fiat", method: "mul", curve: "curve25519_solinas" },
  fiat_curve25519_solinas_mul2: { bridge: "fiat", method: "mul2", curve: "curve25519_solinas" },
  fiat_curve25519_solinas_square: { bridge: "fiat", method: "square", curve: "curve25519_solinas" },
  fiat_p224_mul: { bridge: "fiat", method: "mul", curve: "p224" },
  fiat_p224_square: { bridge: "fiat", method: "square", curve: "p224" },
  fiat_p256_mul: { bridge: "fiat", method: "mul", curve: "p256" },
  fiat_p256_square: { bridge: "fiat", method: "square", curve: "p256" },
  fiat_p384_mul: { bridge: "fiat", method: "mul", curve: "p384" },
  fiat_p384_square: { bridge: "fiat", method: "square", curve: "p384" },
  fiat_p434_mul: { bridge: "fiat", method: "mul", curve: "p434" },
  fiat_p434_square: { bridge: "fiat", method: "square", curve: "p434" },
  fiat_p448_solinas_carry_mul: { bridge: "fiat", method: "mul", curve: "p448_solinas" },
  fiat_p448_solinas_carry_square: { bridge: "fiat", method: "square", curve: "p448_solinas" },
  fiat_p521_carry_mul: { bridge: "fiat", method: "mul", curve: "p521" },
  fiat_p521_carry_square: { bridge: "fiat", method: "square", curve: "p521" },
  fiat_poly1305_carry_mul: { bridge: "fiat", method: "mul", curve: "poly1305" },
  fiat_poly1305_carry_square: { bridge: "fiat", method: "square", curve: "poly1305" },
  fiat_secp256k1_mul: { bridge: "fiat", method: "mul", curve: "secp256k1" },
  fiat_secp256k1_dettman_mul: { bridge: "fiat", method: "mul", curve: "secp256k1_dettman" },
  fiat_secp256k1_square: { bridge: "fiat", method: "square", curve: "secp256k1" },

  // bitcoin curve
  secp256k1_fe_mul_inner: { bridge: "bitcoin-core", method: "mul", curve: "secp256k1" },
  secp256k1_fe_sqr_inner: { bridge: "bitcoin-core", method: "square", curve: "secp256k1" },
};
