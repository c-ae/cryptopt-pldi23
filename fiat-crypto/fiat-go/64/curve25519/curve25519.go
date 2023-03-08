// Code generated by Fiat Cryptography. DO NOT EDIT.
//
// Autogenerated: 'src/ExtractionOCaml/unsaturated_solinas' --lang Go --no-wide-int --relax-primitive-carry-to-bitwidth 32,64 --cmovznz-by-mul --internal-static --package-case flatcase --public-function-case UpperCamelCase --private-function-case camelCase --public-type-case UpperCamelCase --private-type-case camelCase --no-prefix-fiat --doc-newline-in-typedef-bounds --doc-prepend-header 'Code generated by Fiat Cryptography. DO NOT EDIT.' --doc-text-before-function-name '' --doc-text-before-type-name '' --package-name curve25519 '' 64 '(auto)' '2^255 - 19' carry_mul carry_square carry add sub opp selectznz to_bytes from_bytes relax carry_scmul121666 carry_add carry_sub carry_opp
//
// curve description (via package name): curve25519
//
// machine_wordsize = 64 (from "64")
//
// requested operations: carry_mul, carry_square, carry, add, sub, opp, selectznz, to_bytes, from_bytes, relax, carry_scmul121666, carry_add, carry_sub, carry_opp
//
// n = 5 (from "(auto)")
//
// s-c = 2^255 - [(1, 19)] (from "2^255 - 19")
//
// tight_bounds_multiplier = 1 (from "")
//
//
//
// Computed values:
//
//   carry_chain = [0, 1, 2, 3, 4, 0, 1]
//
//   eval z = z[0] + (z[1] << 51) + (z[2] << 102) + (z[3] << 153) + (z[4] << 204)
//
//   bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] << 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] << 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14] << 112) + (z[15] << 120) + (z[16] << 128) + (z[17] << 136) + (z[18] << 144) + (z[19] << 152) + (z[20] << 160) + (z[21] << 168) + (z[22] << 176) + (z[23] << 184) + (z[24] << 192) + (z[25] << 200) + (z[26] << 208) + (z[27] << 216) + (z[28] << 224) + (z[29] << 232) + (z[30] << 240) + (z[31] << 248)
//
//   balance = [0xfffffffffffda, 0xffffffffffffe, 0xffffffffffffe, 0xffffffffffffe, 0xffffffffffffe]
package curve25519

import "math/bits"

type uint1 uint64 // We use uint64 instead of a more narrow type for performance reasons; see https://github.com/mit-plv/fiat-crypto/pull/1006#issuecomment-892625927
type int1 int64 // We use uint64 instead of a more narrow type for performance reasons; see https://github.com/mit-plv/fiat-crypto/pull/1006#issuecomment-892625927

// LooseFieldElement is a field element with loose bounds.
//
// Bounds:
//
//   [[0x0 ~> 0x18000000000000], [0x0 ~> 0x18000000000000], [0x0 ~> 0x18000000000000], [0x0 ~> 0x18000000000000], [0x0 ~> 0x18000000000000]]
type LooseFieldElement [5]uint64

// TightFieldElement is a field element with tight bounds.
//
// Bounds:
//
//   [[0x0 ~> 0x8000000000000], [0x0 ~> 0x8000000000000], [0x0 ~> 0x8000000000000], [0x0 ~> 0x8000000000000], [0x0 ~> 0x8000000000000]]
type TightFieldElement [5]uint64

// addcarryxU51 is an addition with carry.
//
// Postconditions:
//   out1 = (arg1 + arg2 + arg3) mod 2^51
//   out2 = ⌊(arg1 + arg2 + arg3) / 2^51⌋
//
// Input Bounds:
//   arg1: [0x0 ~> 0x1]
//   arg2: [0x0 ~> 0x7ffffffffffff]
//   arg3: [0x0 ~> 0x7ffffffffffff]
// Output Bounds:
//   out1: [0x0 ~> 0x7ffffffffffff]
//   out2: [0x0 ~> 0x1]
func addcarryxU51(out1 *uint64, out2 *uint1, arg1 uint1, arg2 uint64, arg3 uint64) {
	x1 := ((uint64(arg1) + arg2) + arg3)
	x2 := (x1 & 0x7ffffffffffff)
	x3 := uint1((x1 >> 51))
	*out1 = x2
	*out2 = x3
}

// subborrowxU51 is a subtraction with borrow.
//
// Postconditions:
//   out1 = (-arg1 + arg2 + -arg3) mod 2^51
//   out2 = -⌊(-arg1 + arg2 + -arg3) / 2^51⌋
//
// Input Bounds:
//   arg1: [0x0 ~> 0x1]
//   arg2: [0x0 ~> 0x7ffffffffffff]
//   arg3: [0x0 ~> 0x7ffffffffffff]
// Output Bounds:
//   out1: [0x0 ~> 0x7ffffffffffff]
//   out2: [0x0 ~> 0x1]
func subborrowxU51(out1 *uint64, out2 *uint1, arg1 uint1, arg2 uint64, arg3 uint64) {
	x1 := ((int64(arg2) - int64(arg1)) - int64(arg3))
	x2 := int1((x1 >> 51))
	x3 := (uint64(x1) & 0x7ffffffffffff)
	*out1 = x3
	*out2 = (0x0 - uint1(x2))
}

// cmovznzU64 is a single-word conditional move.
//
// Postconditions:
//   out1 = (if arg1 = 0 then arg2 else arg3)
//
// Input Bounds:
//   arg1: [0x0 ~> 0x1]
//   arg2: [0x0 ~> 0xffffffffffffffff]
//   arg3: [0x0 ~> 0xffffffffffffffff]
// Output Bounds:
//   out1: [0x0 ~> 0xffffffffffffffff]
func cmovznzU64(out1 *uint64, arg1 uint1, arg2 uint64, arg3 uint64) {
	x1 := (uint64(arg1) * 0xffffffffffffffff)
	x2 := ((x1 & arg3) | ((^x1) & arg2))
	*out1 = x2
}

// CarryMul multiplies two field elements and reduces the result.
//
// Postconditions:
//   eval out1 mod m = (eval arg1 * eval arg2) mod m
//
func CarryMul(out1 *TightFieldElement, arg1 *LooseFieldElement, arg2 *LooseFieldElement) {
	var x1 uint64
	var x2 uint64
	x2, x1 = bits.Mul64(arg1[4], (arg2[4] * 0x13))
	var x3 uint64
	var x4 uint64
	x4, x3 = bits.Mul64(arg1[4], (arg2[3] * 0x13))
	var x5 uint64
	var x6 uint64
	x6, x5 = bits.Mul64(arg1[4], (arg2[2] * 0x13))
	var x7 uint64
	var x8 uint64
	x8, x7 = bits.Mul64(arg1[4], (arg2[1] * 0x13))
	var x9 uint64
	var x10 uint64
	x10, x9 = bits.Mul64(arg1[3], (arg2[4] * 0x13))
	var x11 uint64
	var x12 uint64
	x12, x11 = bits.Mul64(arg1[3], (arg2[3] * 0x13))
	var x13 uint64
	var x14 uint64
	x14, x13 = bits.Mul64(arg1[3], (arg2[2] * 0x13))
	var x15 uint64
	var x16 uint64
	x16, x15 = bits.Mul64(arg1[2], (arg2[4] * 0x13))
	var x17 uint64
	var x18 uint64
	x18, x17 = bits.Mul64(arg1[2], (arg2[3] * 0x13))
	var x19 uint64
	var x20 uint64
	x20, x19 = bits.Mul64(arg1[1], (arg2[4] * 0x13))
	var x21 uint64
	var x22 uint64
	x22, x21 = bits.Mul64(arg1[4], arg2[0])
	var x23 uint64
	var x24 uint64
	x24, x23 = bits.Mul64(arg1[3], arg2[1])
	var x25 uint64
	var x26 uint64
	x26, x25 = bits.Mul64(arg1[3], arg2[0])
	var x27 uint64
	var x28 uint64
	x28, x27 = bits.Mul64(arg1[2], arg2[2])
	var x29 uint64
	var x30 uint64
	x30, x29 = bits.Mul64(arg1[2], arg2[1])
	var x31 uint64
	var x32 uint64
	x32, x31 = bits.Mul64(arg1[2], arg2[0])
	var x33 uint64
	var x34 uint64
	x34, x33 = bits.Mul64(arg1[1], arg2[3])
	var x35 uint64
	var x36 uint64
	x36, x35 = bits.Mul64(arg1[1], arg2[2])
	var x37 uint64
	var x38 uint64
	x38, x37 = bits.Mul64(arg1[1], arg2[1])
	var x39 uint64
	var x40 uint64
	x40, x39 = bits.Mul64(arg1[1], arg2[0])
	var x41 uint64
	var x42 uint64
	x42, x41 = bits.Mul64(arg1[0], arg2[4])
	var x43 uint64
	var x44 uint64
	x44, x43 = bits.Mul64(arg1[0], arg2[3])
	var x45 uint64
	var x46 uint64
	x46, x45 = bits.Mul64(arg1[0], arg2[2])
	var x47 uint64
	var x48 uint64
	x48, x47 = bits.Mul64(arg1[0], arg2[1])
	var x49 uint64
	var x50 uint64
	x50, x49 = bits.Mul64(arg1[0], arg2[0])
	var x51 uint64
	var x52 uint64
	x51, x52 = bits.Add64(x13, x7, uint64(0x0))
	var x53 uint64
	x53, _ = bits.Add64(x14, x8, uint64(uint1(x52)))
	var x55 uint64
	var x56 uint64
	x55, x56 = bits.Add64(x17, x51, uint64(0x0))
	var x57 uint64
	x57, _ = bits.Add64(x18, x53, uint64(uint1(x56)))
	var x59 uint64
	var x60 uint64
	x59, x60 = bits.Add64(x19, x55, uint64(0x0))
	var x61 uint64
	x61, _ = bits.Add64(x20, x57, uint64(uint1(x60)))
	var x63 uint64
	var x64 uint64
	x63, x64 = bits.Add64(x49, x59, uint64(0x0))
	var x65 uint64
	x65, _ = bits.Add64(x50, x61, uint64(uint1(x64)))
	x67 := ((x63 >> 51) | ((x65 << 13) & 0xffffffffffffffff))
	x68 := (x63 & 0x7ffffffffffff)
	var x69 uint64
	var x70 uint64
	x69, x70 = bits.Add64(x23, x21, uint64(0x0))
	var x71 uint64
	x71, _ = bits.Add64(x24, x22, uint64(uint1(x70)))
	var x73 uint64
	var x74 uint64
	x73, x74 = bits.Add64(x27, x69, uint64(0x0))
	var x75 uint64
	x75, _ = bits.Add64(x28, x71, uint64(uint1(x74)))
	var x77 uint64
	var x78 uint64
	x77, x78 = bits.Add64(x33, x73, uint64(0x0))
	var x79 uint64
	x79, _ = bits.Add64(x34, x75, uint64(uint1(x78)))
	var x81 uint64
	var x82 uint64
	x81, x82 = bits.Add64(x41, x77, uint64(0x0))
	var x83 uint64
	x83, _ = bits.Add64(x42, x79, uint64(uint1(x82)))
	var x85 uint64
	var x86 uint64
	x85, x86 = bits.Add64(x25, x1, uint64(0x0))
	var x87 uint64
	x87, _ = bits.Add64(x26, x2, uint64(uint1(x86)))
	var x89 uint64
	var x90 uint64
	x89, x90 = bits.Add64(x29, x85, uint64(0x0))
	var x91 uint64
	x91, _ = bits.Add64(x30, x87, uint64(uint1(x90)))
	var x93 uint64
	var x94 uint64
	x93, x94 = bits.Add64(x35, x89, uint64(0x0))
	var x95 uint64
	x95, _ = bits.Add64(x36, x91, uint64(uint1(x94)))
	var x97 uint64
	var x98 uint64
	x97, x98 = bits.Add64(x43, x93, uint64(0x0))
	var x99 uint64
	x99, _ = bits.Add64(x44, x95, uint64(uint1(x98)))
	var x101 uint64
	var x102 uint64
	x101, x102 = bits.Add64(x9, x3, uint64(0x0))
	var x103 uint64
	x103, _ = bits.Add64(x10, x4, uint64(uint1(x102)))
	var x105 uint64
	var x106 uint64
	x105, x106 = bits.Add64(x31, x101, uint64(0x0))
	var x107 uint64
	x107, _ = bits.Add64(x32, x103, uint64(uint1(x106)))
	var x109 uint64
	var x110 uint64
	x109, x110 = bits.Add64(x37, x105, uint64(0x0))
	var x111 uint64
	x111, _ = bits.Add64(x38, x107, uint64(uint1(x110)))
	var x113 uint64
	var x114 uint64
	x113, x114 = bits.Add64(x45, x109, uint64(0x0))
	var x115 uint64
	x115, _ = bits.Add64(x46, x111, uint64(uint1(x114)))
	var x117 uint64
	var x118 uint64
	x117, x118 = bits.Add64(x11, x5, uint64(0x0))
	var x119 uint64
	x119, _ = bits.Add64(x12, x6, uint64(uint1(x118)))
	var x121 uint64
	var x122 uint64
	x121, x122 = bits.Add64(x15, x117, uint64(0x0))
	var x123 uint64
	x123, _ = bits.Add64(x16, x119, uint64(uint1(x122)))
	var x125 uint64
	var x126 uint64
	x125, x126 = bits.Add64(x39, x121, uint64(0x0))
	var x127 uint64
	x127, _ = bits.Add64(x40, x123, uint64(uint1(x126)))
	var x129 uint64
	var x130 uint64
	x129, x130 = bits.Add64(x47, x125, uint64(0x0))
	var x131 uint64
	x131, _ = bits.Add64(x48, x127, uint64(uint1(x130)))
	var x133 uint64
	var x134 uint64
	x133, x134 = bits.Add64(x67, x129, uint64(0x0))
	x135 := (uint64(uint1(x134)) + x131)
	x136 := ((x133 >> 51) | ((x135 << 13) & 0xffffffffffffffff))
	x137 := (x133 & 0x7ffffffffffff)
	var x138 uint64
	var x139 uint64
	x138, x139 = bits.Add64(x136, x113, uint64(0x0))
	x140 := (uint64(uint1(x139)) + x115)
	x141 := ((x138 >> 51) | ((x140 << 13) & 0xffffffffffffffff))
	x142 := (x138 & 0x7ffffffffffff)
	var x143 uint64
	var x144 uint64
	x143, x144 = bits.Add64(x141, x97, uint64(0x0))
	x145 := (uint64(uint1(x144)) + x99)
	x146 := ((x143 >> 51) | ((x145 << 13) & 0xffffffffffffffff))
	x147 := (x143 & 0x7ffffffffffff)
	var x148 uint64
	var x149 uint64
	x148, x149 = bits.Add64(x146, x81, uint64(0x0))
	x150 := (uint64(uint1(x149)) + x83)
	x151 := ((x148 >> 51) | ((x150 << 13) & 0xffffffffffffffff))
	x152 := (x148 & 0x7ffffffffffff)
	x153 := (x151 * 0x13)
	x154 := (x68 + x153)
	x155 := (x154 >> 51)
	x156 := (x154 & 0x7ffffffffffff)
	x157 := (x155 + x137)
	x158 := uint1((x157 >> 51))
	x159 := (x157 & 0x7ffffffffffff)
	x160 := (uint64(x158) + x142)
	out1[0] = x156
	out1[1] = x159
	out1[2] = x160
	out1[3] = x147
	out1[4] = x152
}

// CarrySquare squares a field element and reduces the result.
//
// Postconditions:
//   eval out1 mod m = (eval arg1 * eval arg1) mod m
//
func CarrySquare(out1 *TightFieldElement, arg1 *LooseFieldElement) {
	x1 := (arg1[4] * 0x13)
	x2 := (x1 * 0x2)
	x3 := (arg1[4] * 0x2)
	x4 := (arg1[3] * 0x13)
	x5 := (x4 * 0x2)
	x6 := (arg1[3] * 0x2)
	x7 := (arg1[2] * 0x2)
	x8 := (arg1[1] * 0x2)
	var x9 uint64
	var x10 uint64
	x10, x9 = bits.Mul64(arg1[4], x1)
	var x11 uint64
	var x12 uint64
	x12, x11 = bits.Mul64(arg1[3], x2)
	var x13 uint64
	var x14 uint64
	x14, x13 = bits.Mul64(arg1[3], x4)
	var x15 uint64
	var x16 uint64
	x16, x15 = bits.Mul64(arg1[2], x2)
	var x17 uint64
	var x18 uint64
	x18, x17 = bits.Mul64(arg1[2], x5)
	var x19 uint64
	var x20 uint64
	x20, x19 = bits.Mul64(arg1[2], arg1[2])
	var x21 uint64
	var x22 uint64
	x22, x21 = bits.Mul64(arg1[1], x2)
	var x23 uint64
	var x24 uint64
	x24, x23 = bits.Mul64(arg1[1], x6)
	var x25 uint64
	var x26 uint64
	x26, x25 = bits.Mul64(arg1[1], x7)
	var x27 uint64
	var x28 uint64
	x28, x27 = bits.Mul64(arg1[1], arg1[1])
	var x29 uint64
	var x30 uint64
	x30, x29 = bits.Mul64(arg1[0], x3)
	var x31 uint64
	var x32 uint64
	x32, x31 = bits.Mul64(arg1[0], x6)
	var x33 uint64
	var x34 uint64
	x34, x33 = bits.Mul64(arg1[0], x7)
	var x35 uint64
	var x36 uint64
	x36, x35 = bits.Mul64(arg1[0], x8)
	var x37 uint64
	var x38 uint64
	x38, x37 = bits.Mul64(arg1[0], arg1[0])
	var x39 uint64
	var x40 uint64
	x39, x40 = bits.Add64(x21, x17, uint64(0x0))
	var x41 uint64
	x41, _ = bits.Add64(x22, x18, uint64(uint1(x40)))
	var x43 uint64
	var x44 uint64
	x43, x44 = bits.Add64(x37, x39, uint64(0x0))
	var x45 uint64
	x45, _ = bits.Add64(x38, x41, uint64(uint1(x44)))
	x47 := ((x43 >> 51) | ((x45 << 13) & 0xffffffffffffffff))
	x48 := (x43 & 0x7ffffffffffff)
	var x49 uint64
	var x50 uint64
	x49, x50 = bits.Add64(x23, x19, uint64(0x0))
	var x51 uint64
	x51, _ = bits.Add64(x24, x20, uint64(uint1(x50)))
	var x53 uint64
	var x54 uint64
	x53, x54 = bits.Add64(x29, x49, uint64(0x0))
	var x55 uint64
	x55, _ = bits.Add64(x30, x51, uint64(uint1(x54)))
	var x57 uint64
	var x58 uint64
	x57, x58 = bits.Add64(x25, x9, uint64(0x0))
	var x59 uint64
	x59, _ = bits.Add64(x26, x10, uint64(uint1(x58)))
	var x61 uint64
	var x62 uint64
	x61, x62 = bits.Add64(x31, x57, uint64(0x0))
	var x63 uint64
	x63, _ = bits.Add64(x32, x59, uint64(uint1(x62)))
	var x65 uint64
	var x66 uint64
	x65, x66 = bits.Add64(x27, x11, uint64(0x0))
	var x67 uint64
	x67, _ = bits.Add64(x28, x12, uint64(uint1(x66)))
	var x69 uint64
	var x70 uint64
	x69, x70 = bits.Add64(x33, x65, uint64(0x0))
	var x71 uint64
	x71, _ = bits.Add64(x34, x67, uint64(uint1(x70)))
	var x73 uint64
	var x74 uint64
	x73, x74 = bits.Add64(x15, x13, uint64(0x0))
	var x75 uint64
	x75, _ = bits.Add64(x16, x14, uint64(uint1(x74)))
	var x77 uint64
	var x78 uint64
	x77, x78 = bits.Add64(x35, x73, uint64(0x0))
	var x79 uint64
	x79, _ = bits.Add64(x36, x75, uint64(uint1(x78)))
	var x81 uint64
	var x82 uint64
	x81, x82 = bits.Add64(x47, x77, uint64(0x0))
	x83 := (uint64(uint1(x82)) + x79)
	x84 := ((x81 >> 51) | ((x83 << 13) & 0xffffffffffffffff))
	x85 := (x81 & 0x7ffffffffffff)
	var x86 uint64
	var x87 uint64
	x86, x87 = bits.Add64(x84, x69, uint64(0x0))
	x88 := (uint64(uint1(x87)) + x71)
	x89 := ((x86 >> 51) | ((x88 << 13) & 0xffffffffffffffff))
	x90 := (x86 & 0x7ffffffffffff)
	var x91 uint64
	var x92 uint64
	x91, x92 = bits.Add64(x89, x61, uint64(0x0))
	x93 := (uint64(uint1(x92)) + x63)
	x94 := ((x91 >> 51) | ((x93 << 13) & 0xffffffffffffffff))
	x95 := (x91 & 0x7ffffffffffff)
	var x96 uint64
	var x97 uint64
	x96, x97 = bits.Add64(x94, x53, uint64(0x0))
	x98 := (uint64(uint1(x97)) + x55)
	x99 := ((x96 >> 51) | ((x98 << 13) & 0xffffffffffffffff))
	x100 := (x96 & 0x7ffffffffffff)
	x101 := (x99 * 0x13)
	x102 := (x48 + x101)
	x103 := (x102 >> 51)
	x104 := (x102 & 0x7ffffffffffff)
	x105 := (x103 + x85)
	x106 := uint1((x105 >> 51))
	x107 := (x105 & 0x7ffffffffffff)
	x108 := (uint64(x106) + x90)
	out1[0] = x104
	out1[1] = x107
	out1[2] = x108
	out1[3] = x95
	out1[4] = x100
}

// Carry reduces a field element.
//
// Postconditions:
//   eval out1 mod m = eval arg1 mod m
//
func Carry(out1 *TightFieldElement, arg1 *LooseFieldElement) {
	x1 := arg1[0]
	x2 := ((x1 >> 51) + arg1[1])
	x3 := ((x2 >> 51) + arg1[2])
	x4 := ((x3 >> 51) + arg1[3])
	x5 := ((x4 >> 51) + arg1[4])
	x6 := ((x1 & 0x7ffffffffffff) + ((x5 >> 51) * 0x13))
	x7 := (uint64(uint1((x6 >> 51))) + (x2 & 0x7ffffffffffff))
	x8 := (x6 & 0x7ffffffffffff)
	x9 := (x7 & 0x7ffffffffffff)
	x10 := (uint64(uint1((x7 >> 51))) + (x3 & 0x7ffffffffffff))
	x11 := (x4 & 0x7ffffffffffff)
	x12 := (x5 & 0x7ffffffffffff)
	out1[0] = x8
	out1[1] = x9
	out1[2] = x10
	out1[3] = x11
	out1[4] = x12
}

// Add adds two field elements.
//
// Postconditions:
//   eval out1 mod m = (eval arg1 + eval arg2) mod m
//
func Add(out1 *LooseFieldElement, arg1 *TightFieldElement, arg2 *TightFieldElement) {
	x1 := (arg1[0] + arg2[0])
	x2 := (arg1[1] + arg2[1])
	x3 := (arg1[2] + arg2[2])
	x4 := (arg1[3] + arg2[3])
	x5 := (arg1[4] + arg2[4])
	out1[0] = x1
	out1[1] = x2
	out1[2] = x3
	out1[3] = x4
	out1[4] = x5
}

// Sub subtracts two field elements.
//
// Postconditions:
//   eval out1 mod m = (eval arg1 - eval arg2) mod m
//
func Sub(out1 *LooseFieldElement, arg1 *TightFieldElement, arg2 *TightFieldElement) {
	x1 := ((0xfffffffffffda + arg1[0]) - arg2[0])
	x2 := ((0xffffffffffffe + arg1[1]) - arg2[1])
	x3 := ((0xffffffffffffe + arg1[2]) - arg2[2])
	x4 := ((0xffffffffffffe + arg1[3]) - arg2[3])
	x5 := ((0xffffffffffffe + arg1[4]) - arg2[4])
	out1[0] = x1
	out1[1] = x2
	out1[2] = x3
	out1[3] = x4
	out1[4] = x5
}

// Opp negates a field element.
//
// Postconditions:
//   eval out1 mod m = -eval arg1 mod m
//
func Opp(out1 *LooseFieldElement, arg1 *TightFieldElement) {
	x1 := (0xfffffffffffda - arg1[0])
	x2 := (0xffffffffffffe - arg1[1])
	x3 := (0xffffffffffffe - arg1[2])
	x4 := (0xffffffffffffe - arg1[3])
	x5 := (0xffffffffffffe - arg1[4])
	out1[0] = x1
	out1[1] = x2
	out1[2] = x3
	out1[3] = x4
	out1[4] = x5
}

// Selectznz is a multi-limb conditional select.
//
// Postconditions:
//   out1 = (if arg1 = 0 then arg2 else arg3)
//
// Input Bounds:
//   arg1: [0x0 ~> 0x1]
//   arg2: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
//   arg3: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
// Output Bounds:
//   out1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
func Selectznz(out1 *[5]uint64, arg1 uint1, arg2 *[5]uint64, arg3 *[5]uint64) {
	var x1 uint64
	cmovznzU64(&x1, arg1, arg2[0], arg3[0])
	var x2 uint64
	cmovznzU64(&x2, arg1, arg2[1], arg3[1])
	var x3 uint64
	cmovznzU64(&x3, arg1, arg2[2], arg3[2])
	var x4 uint64
	cmovznzU64(&x4, arg1, arg2[3], arg3[3])
	var x5 uint64
	cmovznzU64(&x5, arg1, arg2[4], arg3[4])
	out1[0] = x1
	out1[1] = x2
	out1[2] = x3
	out1[3] = x4
	out1[4] = x5
}

// ToBytes serializes a field element to bytes in little-endian order.
//
// Postconditions:
//   out1 = map (λ x, ⌊((eval arg1 mod m) mod 2^(8 * (x + 1))) / 2^(8 * x)⌋) [0..31]
//
// Output Bounds:
//   out1: [[0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0x7f]]
func ToBytes(out1 *[32]uint8, arg1 *TightFieldElement) {
	var x1 uint64
	var x2 uint1
	subborrowxU51(&x1, &x2, 0x0, arg1[0], 0x7ffffffffffed)
	var x3 uint64
	var x4 uint1
	subborrowxU51(&x3, &x4, x2, arg1[1], 0x7ffffffffffff)
	var x5 uint64
	var x6 uint1
	subborrowxU51(&x5, &x6, x4, arg1[2], 0x7ffffffffffff)
	var x7 uint64
	var x8 uint1
	subborrowxU51(&x7, &x8, x6, arg1[3], 0x7ffffffffffff)
	var x9 uint64
	var x10 uint1
	subborrowxU51(&x9, &x10, x8, arg1[4], 0x7ffffffffffff)
	var x11 uint64
	cmovznzU64(&x11, x10, uint64(0x0), 0xffffffffffffffff)
	var x12 uint64
	var x13 uint1
	addcarryxU51(&x12, &x13, 0x0, x1, (x11 & 0x7ffffffffffed))
	var x14 uint64
	var x15 uint1
	addcarryxU51(&x14, &x15, x13, x3, (x11 & 0x7ffffffffffff))
	var x16 uint64
	var x17 uint1
	addcarryxU51(&x16, &x17, x15, x5, (x11 & 0x7ffffffffffff))
	var x18 uint64
	var x19 uint1
	addcarryxU51(&x18, &x19, x17, x7, (x11 & 0x7ffffffffffff))
	var x20 uint64
	var x21 uint1
	addcarryxU51(&x20, &x21, x19, x9, (x11 & 0x7ffffffffffff))
	x22 := (x20 << 4)
	x23 := (x18 * uint64(0x2))
	x24 := (x16 << 6)
	x25 := (x14 << 3)
	x26 := (uint8(x12) & 0xff)
	x27 := (x12 >> 8)
	x28 := (uint8(x27) & 0xff)
	x29 := (x27 >> 8)
	x30 := (uint8(x29) & 0xff)
	x31 := (x29 >> 8)
	x32 := (uint8(x31) & 0xff)
	x33 := (x31 >> 8)
	x34 := (uint8(x33) & 0xff)
	x35 := (x33 >> 8)
	x36 := (uint8(x35) & 0xff)
	x37 := uint8((x35 >> 8))
	x38 := (x25 + uint64(x37))
	x39 := (uint8(x38) & 0xff)
	x40 := (x38 >> 8)
	x41 := (uint8(x40) & 0xff)
	x42 := (x40 >> 8)
	x43 := (uint8(x42) & 0xff)
	x44 := (x42 >> 8)
	x45 := (uint8(x44) & 0xff)
	x46 := (x44 >> 8)
	x47 := (uint8(x46) & 0xff)
	x48 := (x46 >> 8)
	x49 := (uint8(x48) & 0xff)
	x50 := uint8((x48 >> 8))
	x51 := (x24 + uint64(x50))
	x52 := (uint8(x51) & 0xff)
	x53 := (x51 >> 8)
	x54 := (uint8(x53) & 0xff)
	x55 := (x53 >> 8)
	x56 := (uint8(x55) & 0xff)
	x57 := (x55 >> 8)
	x58 := (uint8(x57) & 0xff)
	x59 := (x57 >> 8)
	x60 := (uint8(x59) & 0xff)
	x61 := (x59 >> 8)
	x62 := (uint8(x61) & 0xff)
	x63 := (x61 >> 8)
	x64 := (uint8(x63) & 0xff)
	x65 := uint1((x63 >> 8))
	x66 := (x23 + uint64(x65))
	x67 := (uint8(x66) & 0xff)
	x68 := (x66 >> 8)
	x69 := (uint8(x68) & 0xff)
	x70 := (x68 >> 8)
	x71 := (uint8(x70) & 0xff)
	x72 := (x70 >> 8)
	x73 := (uint8(x72) & 0xff)
	x74 := (x72 >> 8)
	x75 := (uint8(x74) & 0xff)
	x76 := (x74 >> 8)
	x77 := (uint8(x76) & 0xff)
	x78 := uint8((x76 >> 8))
	x79 := (x22 + uint64(x78))
	x80 := (uint8(x79) & 0xff)
	x81 := (x79 >> 8)
	x82 := (uint8(x81) & 0xff)
	x83 := (x81 >> 8)
	x84 := (uint8(x83) & 0xff)
	x85 := (x83 >> 8)
	x86 := (uint8(x85) & 0xff)
	x87 := (x85 >> 8)
	x88 := (uint8(x87) & 0xff)
	x89 := (x87 >> 8)
	x90 := (uint8(x89) & 0xff)
	x91 := uint8((x89 >> 8))
	out1[0] = x26
	out1[1] = x28
	out1[2] = x30
	out1[3] = x32
	out1[4] = x34
	out1[5] = x36
	out1[6] = x39
	out1[7] = x41
	out1[8] = x43
	out1[9] = x45
	out1[10] = x47
	out1[11] = x49
	out1[12] = x52
	out1[13] = x54
	out1[14] = x56
	out1[15] = x58
	out1[16] = x60
	out1[17] = x62
	out1[18] = x64
	out1[19] = x67
	out1[20] = x69
	out1[21] = x71
	out1[22] = x73
	out1[23] = x75
	out1[24] = x77
	out1[25] = x80
	out1[26] = x82
	out1[27] = x84
	out1[28] = x86
	out1[29] = x88
	out1[30] = x90
	out1[31] = x91
}

// FromBytes deserializes a field element from bytes in little-endian order.
//
// Postconditions:
//   eval out1 mod m = bytes_eval arg1 mod m
//
// Input Bounds:
//   arg1: [[0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0x7f]]
func FromBytes(out1 *TightFieldElement, arg1 *[32]uint8) {
	x1 := (uint64(arg1[31]) << 44)
	x2 := (uint64(arg1[30]) << 36)
	x3 := (uint64(arg1[29]) << 28)
	x4 := (uint64(arg1[28]) << 20)
	x5 := (uint64(arg1[27]) << 12)
	x6 := (uint64(arg1[26]) << 4)
	x7 := (uint64(arg1[25]) << 47)
	x8 := (uint64(arg1[24]) << 39)
	x9 := (uint64(arg1[23]) << 31)
	x10 := (uint64(arg1[22]) << 23)
	x11 := (uint64(arg1[21]) << 15)
	x12 := (uint64(arg1[20]) << 7)
	x13 := (uint64(arg1[19]) << 50)
	x14 := (uint64(arg1[18]) << 42)
	x15 := (uint64(arg1[17]) << 34)
	x16 := (uint64(arg1[16]) << 26)
	x17 := (uint64(arg1[15]) << 18)
	x18 := (uint64(arg1[14]) << 10)
	x19 := (uint64(arg1[13]) << 2)
	x20 := (uint64(arg1[12]) << 45)
	x21 := (uint64(arg1[11]) << 37)
	x22 := (uint64(arg1[10]) << 29)
	x23 := (uint64(arg1[9]) << 21)
	x24 := (uint64(arg1[8]) << 13)
	x25 := (uint64(arg1[7]) << 5)
	x26 := (uint64(arg1[6]) << 48)
	x27 := (uint64(arg1[5]) << 40)
	x28 := (uint64(arg1[4]) << 32)
	x29 := (uint64(arg1[3]) << 24)
	x30 := (uint64(arg1[2]) << 16)
	x31 := (uint64(arg1[1]) << 8)
	x32 := arg1[0]
	x33 := (x31 + uint64(x32))
	x34 := (x30 + x33)
	x35 := (x29 + x34)
	x36 := (x28 + x35)
	x37 := (x27 + x36)
	x38 := (x26 + x37)
	x39 := (x38 & 0x7ffffffffffff)
	x40 := uint8((x38 >> 51))
	x41 := (x25 + uint64(x40))
	x42 := (x24 + x41)
	x43 := (x23 + x42)
	x44 := (x22 + x43)
	x45 := (x21 + x44)
	x46 := (x20 + x45)
	x47 := (x46 & 0x7ffffffffffff)
	x48 := uint8((x46 >> 51))
	x49 := (x19 + uint64(x48))
	x50 := (x18 + x49)
	x51 := (x17 + x50)
	x52 := (x16 + x51)
	x53 := (x15 + x52)
	x54 := (x14 + x53)
	x55 := (x13 + x54)
	x56 := (x55 & 0x7ffffffffffff)
	x57 := uint8((x55 >> 51))
	x58 := (x12 + uint64(x57))
	x59 := (x11 + x58)
	x60 := (x10 + x59)
	x61 := (x9 + x60)
	x62 := (x8 + x61)
	x63 := (x7 + x62)
	x64 := (x63 & 0x7ffffffffffff)
	x65 := uint8((x63 >> 51))
	x66 := (x6 + uint64(x65))
	x67 := (x5 + x66)
	x68 := (x4 + x67)
	x69 := (x3 + x68)
	x70 := (x2 + x69)
	x71 := (x1 + x70)
	out1[0] = x39
	out1[1] = x47
	out1[2] = x56
	out1[3] = x64
	out1[4] = x71
}

// Relax is the identity function converting from tight field elements to loose field elements.
//
// Postconditions:
//   out1 = arg1
//
func Relax(out1 *LooseFieldElement, arg1 *TightFieldElement) {
	x1 := arg1[0]
	x2 := arg1[1]
	x3 := arg1[2]
	x4 := arg1[3]
	x5 := arg1[4]
	out1[0] = x1
	out1[1] = x2
	out1[2] = x3
	out1[3] = x4
	out1[4] = x5
}

// CarryScmul121666 multiplies a field element by 121666 and reduces the result.
//
// Postconditions:
//   eval out1 mod m = (121666 * eval arg1) mod m
//
func CarryScmul121666(out1 *TightFieldElement, arg1 *LooseFieldElement) {
	var x1 uint64
	var x2 uint64
	x2, x1 = bits.Mul64(0x1db42, arg1[4])
	var x3 uint64
	var x4 uint64
	x4, x3 = bits.Mul64(0x1db42, arg1[3])
	var x5 uint64
	var x6 uint64
	x6, x5 = bits.Mul64(0x1db42, arg1[2])
	var x7 uint64
	var x8 uint64
	x8, x7 = bits.Mul64(0x1db42, arg1[1])
	var x9 uint64
	var x10 uint64
	x10, x9 = bits.Mul64(0x1db42, arg1[0])
	x11 := ((x9 >> 51) | ((x10 << 13) & 0xffffffffffffffff))
	x12 := (x9 & 0x7ffffffffffff)
	var x13 uint64
	var x14 uint64
	x13, x14 = bits.Add64(x11, x7, uint64(0x0))
	x15 := (uint64(uint1(x14)) + x8)
	x16 := ((x13 >> 51) | ((x15 << 13) & 0xffffffffffffffff))
	x17 := (x13 & 0x7ffffffffffff)
	var x18 uint64
	var x19 uint64
	x18, x19 = bits.Add64(x16, x5, uint64(0x0))
	x20 := (uint64(uint1(x19)) + x6)
	x21 := ((x18 >> 51) | ((x20 << 13) & 0xffffffffffffffff))
	x22 := (x18 & 0x7ffffffffffff)
	var x23 uint64
	var x24 uint64
	x23, x24 = bits.Add64(x21, x3, uint64(0x0))
	x25 := (uint64(uint1(x24)) + x4)
	x26 := ((x23 >> 51) | ((x25 << 13) & 0xffffffffffffffff))
	x27 := (x23 & 0x7ffffffffffff)
	var x28 uint64
	var x29 uint64
	x28, x29 = bits.Add64(x26, x1, uint64(0x0))
	x30 := (uint64(uint1(x29)) + x2)
	x31 := ((x28 >> 51) | ((x30 << 13) & 0xffffffffffffffff))
	x32 := (x28 & 0x7ffffffffffff)
	x33 := (x31 * 0x13)
	x34 := (x12 + x33)
	x35 := uint1((x34 >> 51))
	x36 := (x34 & 0x7ffffffffffff)
	x37 := (uint64(x35) + x17)
	x38 := uint1((x37 >> 51))
	x39 := (x37 & 0x7ffffffffffff)
	x40 := (uint64(x38) + x22)
	out1[0] = x36
	out1[1] = x39
	out1[2] = x40
	out1[3] = x27
	out1[4] = x32
}

// CarryAdd adds two field elements.
//
// Postconditions:
//   eval out1 mod m = (eval arg1 + eval arg2) mod m
//
func CarryAdd(out1 *TightFieldElement, arg1 *TightFieldElement, arg2 *TightFieldElement) {
	x1 := (arg1[0] + arg2[0])
	x2 := ((x1 >> 51) + (arg1[1] + arg2[1]))
	x3 := ((x2 >> 51) + (arg1[2] + arg2[2]))
	x4 := ((x3 >> 51) + (arg1[3] + arg2[3]))
	x5 := ((x4 >> 51) + (arg1[4] + arg2[4]))
	x6 := ((x1 & 0x7ffffffffffff) + ((x5 >> 51) * 0x13))
	x7 := (uint64(uint1((x6 >> 51))) + (x2 & 0x7ffffffffffff))
	x8 := (x6 & 0x7ffffffffffff)
	x9 := (x7 & 0x7ffffffffffff)
	x10 := (uint64(uint1((x7 >> 51))) + (x3 & 0x7ffffffffffff))
	x11 := (x4 & 0x7ffffffffffff)
	x12 := (x5 & 0x7ffffffffffff)
	out1[0] = x8
	out1[1] = x9
	out1[2] = x10
	out1[3] = x11
	out1[4] = x12
}

// CarrySub subtracts two field elements.
//
// Postconditions:
//   eval out1 mod m = (eval arg1 - eval arg2) mod m
//
func CarrySub(out1 *TightFieldElement, arg1 *TightFieldElement, arg2 *TightFieldElement) {
	x1 := ((0xfffffffffffda + arg1[0]) - arg2[0])
	x2 := ((x1 >> 51) + ((0xffffffffffffe + arg1[1]) - arg2[1]))
	x3 := ((x2 >> 51) + ((0xffffffffffffe + arg1[2]) - arg2[2]))
	x4 := ((x3 >> 51) + ((0xffffffffffffe + arg1[3]) - arg2[3]))
	x5 := ((x4 >> 51) + ((0xffffffffffffe + arg1[4]) - arg2[4]))
	x6 := ((x1 & 0x7ffffffffffff) + ((x5 >> 51) * 0x13))
	x7 := (uint64(uint1((x6 >> 51))) + (x2 & 0x7ffffffffffff))
	x8 := (x6 & 0x7ffffffffffff)
	x9 := (x7 & 0x7ffffffffffff)
	x10 := (uint64(uint1((x7 >> 51))) + (x3 & 0x7ffffffffffff))
	x11 := (x4 & 0x7ffffffffffff)
	x12 := (x5 & 0x7ffffffffffff)
	out1[0] = x8
	out1[1] = x9
	out1[2] = x10
	out1[3] = x11
	out1[4] = x12
}

// CarryOpp negates a field element.
//
// Postconditions:
//   eval out1 mod m = -eval arg1 mod m
//
func CarryOpp(out1 *TightFieldElement, arg1 *TightFieldElement) {
	x1 := (0xfffffffffffda - arg1[0])
	x2 := (uint64(uint1((x1 >> 51))) + (0xffffffffffffe - arg1[1]))
	x3 := (uint64(uint1((x2 >> 51))) + (0xffffffffffffe - arg1[2]))
	x4 := (uint64(uint1((x3 >> 51))) + (0xffffffffffffe - arg1[3]))
	x5 := (uint64(uint1((x4 >> 51))) + (0xffffffffffffe - arg1[4]))
	x6 := ((x1 & 0x7ffffffffffff) + (uint64(uint1((x5 >> 51))) * 0x13))
	x7 := (uint64(uint1((x6 >> 51))) + (x2 & 0x7ffffffffffff))
	x8 := (x6 & 0x7ffffffffffff)
	x9 := (x7 & 0x7ffffffffffff)
	x10 := (uint64(uint1((x7 >> 51))) + (x3 & 0x7ffffffffffff))
	x11 := (x4 & 0x7ffffffffffff)
	x12 := (x5 & 0x7ffffffffffff)
	out1[0] = x8
	out1[1] = x9
	out1[2] = x10
	out1[3] = x11
	out1[4] = x12
}