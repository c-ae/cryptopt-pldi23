// Autogenerated: 'src/ExtractionOCaml/dettman_multiplication' --lang Zig --internal-static --public-function-case camelCase --private-function-case camelCase --public-type-case UpperCamelCase --private-type-case UpperCamelCase --no-prefix-fiat --package-name secp256k1_dettman '' 64 5 48 '2^256 - 4294968273' mul
// curve description (via package name): secp256k1_dettman
// machine_wordsize = 64 (from "64")
// requested operations: mul
// n = 5 (from "5")
// last_limb_width = 48 (from "48")
// s-c = 2^256 - [(1, 4294968273)] (from "2^256 - 4294968273")
// inbounds_multiplier: None (from "")
//
// Computed values:
//
//

const std = @import("std");
const mode = @import("builtin").mode; // Checked arithmetic is disabled in non-debug modes to avoid side channels

inline fn cast(comptime DestType: type, target: anytype) DestType {
    @setEvalBranchQuota(10000);
    if (@typeInfo(@TypeOf(target)) == .Int) {
        const dest = @typeInfo(DestType).Int;
        const source = @typeInfo(@TypeOf(target)).Int;
        if (dest.bits < source.bits) {
            return @bitCast(DestType, @truncate(std.meta.Int(source.signedness, dest.bits), target));
        } else {
            return @bitCast(DestType, @as(std.meta.Int(source.signedness, dest.bits), target));
        }
    }
    return @as(DestType, target);
}

/// The function mul multiplies two field elements.
///
/// Postconditions:
///   eval out1 mod 115792089237316195423570985008687907853269984665640564039457584007908834671663 = (eval arg1 * eval arg2) mod 115792089237316195423570985008687907853269984665640564039457584007908834671663
///
/// Input Bounds:
///   arg1: [[0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1fffffffffffe]]
///   arg2: [[0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1fffffffffffe]]
/// Output Bounds:
///   out1: [[0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x1ffffffffffffe], [0x0 ~> 0x17fffffffffff]]
pub fn mul(out1: *[5]u64, arg1: [5]u64, arg2: [5]u64) void {
    @setRuntimeSafety(mode == .Debug);

    const x1 = (cast(u128, (arg1[4])) * cast(u128, (arg2[4])));
    const x2 = cast(u64, (x1 >> 52));
    const x3 = cast(u64, (x1 & cast(u128, 0xfffffffffffff)));
    const x4 = (((cast(u128, (arg1[0])) * cast(u128, (arg2[3]))) + ((cast(u128, (arg1[1])) * cast(u128, (arg2[2]))) + ((cast(u128, (arg1[2])) * cast(u128, (arg2[1]))) + (cast(u128, (arg1[3])) * cast(u128, (arg2[0])))))) + (cast(u128, x3) * cast(u128, 0x1000003d10)));
    const x5 = cast(u64, (x4 >> 52));
    const x6 = cast(u64, (x4 & cast(u128, 0xfffffffffffff)));
    const x7 = ((((cast(u128, (arg1[0])) * cast(u128, (arg2[4]))) + ((cast(u128, (arg1[1])) * cast(u128, (arg2[3]))) + ((cast(u128, (arg1[2])) * cast(u128, (arg2[2]))) + ((cast(u128, (arg1[3])) * cast(u128, (arg2[1]))) + (cast(u128, (arg1[4])) * cast(u128, (arg2[0]))))))) + cast(u128, x5)) + (cast(u128, x2) * cast(u128, 0x1000003d10)));
    const x8 = cast(u64, (x7 >> 52));
    const x9 = cast(u64, (x7 & cast(u128, 0xfffffffffffff)));
    const x10 = (x9 >> 48);
    const x11 = (x9 & 0xffffffffffff);
    const x12 = (((cast(u128, (arg1[1])) * cast(u128, (arg2[4]))) + ((cast(u128, (arg1[2])) * cast(u128, (arg2[3]))) + ((cast(u128, (arg1[3])) * cast(u128, (arg2[2]))) + (cast(u128, (arg1[4])) * cast(u128, (arg2[1])))))) + cast(u128, x8));
    const x13 = cast(u64, (x12 >> 52));
    const x14 = cast(u64, (x12 & cast(u128, 0xfffffffffffff)));
    const x15 = ((cast(u128, (arg1[0])) * cast(u128, (arg2[0]))) + (cast(u128, ((x14 << 4) + x10)) * cast(u128, 0x1000003d1)));
    const x16 = cast(u64, (x15 >> 52));
    const x17 = cast(u64, (x15 & cast(u128, 0xfffffffffffff)));
    const x18 = (((cast(u128, (arg1[2])) * cast(u128, (arg2[4]))) + ((cast(u128, (arg1[3])) * cast(u128, (arg2[3]))) + (cast(u128, (arg1[4])) * cast(u128, (arg2[2]))))) + cast(u128, x13));
    const x19 = cast(u64, (x18 >> 52));
    const x20 = cast(u64, (x18 & cast(u128, 0xfffffffffffff)));
    const x21 = ((((cast(u128, (arg1[0])) * cast(u128, (arg2[1]))) + (cast(u128, (arg1[1])) * cast(u128, (arg2[0])))) + cast(u128, x16)) + (cast(u128, x20) * cast(u128, 0x1000003d10)));
    const x22 = cast(u64, (x21 >> 52));
    const x23 = cast(u64, (x21 & cast(u128, 0xfffffffffffff)));
    const x24 = (((cast(u128, (arg1[3])) * cast(u128, (arg2[4]))) + (cast(u128, (arg1[4])) * cast(u128, (arg2[3])))) + cast(u128, x19));
    const x25 = cast(u64, (x24 >> 52));
    const x26 = cast(u64, (x24 & cast(u128, 0xfffffffffffff)));
    const x27 = ((((cast(u128, (arg1[0])) * cast(u128, (arg2[2]))) + ((cast(u128, (arg1[1])) * cast(u128, (arg2[1]))) + (cast(u128, (arg1[2])) * cast(u128, (arg2[0]))))) + cast(u128, x22)) + (cast(u128, x26) * cast(u128, 0x1000003d10)));
    const x28 = cast(u64, (x27 >> 52));
    const x29 = cast(u64, (x27 & cast(u128, 0xfffffffffffff)));
    const x30 = (cast(u128, (x6 + x28)) + (cast(u128, x25) * cast(u128, 0x1000003d10)));
    const x31 = cast(u64, (x30 >> 52));
    const x32 = cast(u64, (x30 & cast(u128, 0xfffffffffffff)));
    const x33 = (x11 + x31);
    out1[0] = x17;
    out1[1] = x23;
    out1[2] = x29;
    out1[3] = x32;
    out1[4] = x33;
}
