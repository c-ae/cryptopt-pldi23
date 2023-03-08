#!/usr/bin/env bash

set -e # die on error

readonly result_dir=/root/CryptOpt/results
readonly convert=/root/CryptOpt/modules/scripts/convert/intel2att.sh
readonly supercop_dir=/root/supercop/

get_fastest() {
  find "${1}" -name 'seed000*.asm' |
    awk -F_ '{ printf "%s@%s\n", $0, $NF }' |
    sort --field-separator=@ --key=2r |
    awk -F@ '{ print $1 }' |
    head --lines 1
}

convert_all() {
  dest="${1}"
  bridge="${2}"

  for method in "${@:3}"; do
    echo getting fastest from "${result_dir}/${bridge}/${method}"
    fastest=$(get_fastest "${result_dir}/${bridge}/${method}")
    ${convert} --crypto-namespace "${fastest}" >"${dest}/${method}.S"
    echo "${fastest} - >${dest}/${method}.S"
  done
}

echo "Copying asm files for Curve25519-fe51..."
convert_all \
  ${supercop_dir}/crypto_scalarmult/curve25519/openssl-fe51-cryptopt/ \
  fiat \
  fiat_curve25519_carry_square fiat_curve25519_carry_mul

echo "Copying asm files for Curve25519-fe64..."
convert_all \
  ${supercop_dir}/crypto_scalarmult/curve25519/openssl-fe64-cryptopt/ \
  fiat \
  fiat_curve25519_solinas_square fiat_curve25519_solinas_mul

echo "Copying asm files for Bitcoin (CS1), verified..."
convert_all \
  ${supercop_dir}/crypto_scalarmult/secp256k1/libsecp256k1-ots-cryptopt-dettman/ \
  fiat \
  fiat_secp256k1_dettman_mul

echo "Copying asm files for Bitcoin (CS2), not-verified..."
convert_all \
  ${supercop_dir}/crypto_scalarmult/secp256k1/libsecp256k1-ots-cryptopt-bcc/ \
  bitcoin-core \
  secp256k1_fe_mul_inner secp256k1_fe_sqr_inner

printf "\n\033[32mDone.\033[0m. You can run the SUPERCOP benchmark now.\nExecute ./V_3_run_supercop_benchmark.sh\n"
