#!/usr/bin/env bash

# from do-part:12
shorthostname=$(hostname | sed 's/\..*//' | tr -cd '[a-z][A-Z][0-9]' | tr '[A-Z]' '[a-z]')

dir="./bench/${shorthostname}"
datafile="${dir}/data"

# in the docker build the hostname is 'buildkitsandbox' and because we ./bench.sh init in the sandbox, we dont have it in the current hostname. This will move it accordingly
if [[ ! -d ${dir} && -d ./bench/buildkitsandbox ]]; then
  mv ./bench/buildkitsandbox "${dir}"
fi

reset_supercop_bench_dir() {
  ./do-part init

  # independent
  ./do-part crypto_verify 32
  ./do-part crypto_core salsa20
  ./do-part crypto_stream aes256ctr
  ./do-part cryptopp

  # needs cryptopp
  ./do-part crypto_stream chacha20

  # needs core_salsa20
  ./do-part crypto_stream salsa20

  # needs stream{aes256ctr,chacha20,salsa20}
  ./do-part crypto_rng
}

eval_data() {
  grep -e '\(ok\|unknown\) ' "${datafile}" |
    sed -re 's/^.*(ok|unknown) ([[:digit:]]+)( [[:digit:]]+){2} ([[:graph:]_]+\/){2}/\2 /' -e 's/(-O.).*$/\1/' |
    sort -g |
    awk 'BEGIN{
map["sandy2x"]="sandy2x"; \
map["amd64-51"]="amd64-51"; \
map["amd64-64"]="amd64-64"; \
map["donna"]="donna"; \
map["donna_c64"]="donna-c64"; \
map["openssl-c-ots"]="OSSL ots"; \
map["openssl-ots"]="OSSL fe-51 ots"; \
map["openssl-fe51-cryptopt"]="OSSL fe-51 + CryptOpt"; \
map["openssl-fe64-ots"]="OSSL fe-64 ots"; \
map["openssl-fe64-cryptopt"]="OSSL fe-64 + CryptOpt"; \
map["everest-hacl-64"]="HACL* fe-64"; \
map["libsecp256k1-ots"]="libsecp256k1 (ASM)"; \
map["libsecp256k1-c-ots"]="libsecp256k1 (C)"; \
map["libsecp256k1-ots-cryptopt-dettman"]="libsecp256k1 + CryptOpt"; \
map["libsecp256k1-ots-cryptopt-bcc"]="libsecp256k1 + CryptOpt (CS2)"; \
} { if (!a[$2]++) printf "%35s %20s\n", map[$2], $1}' |
    sed -e "s/\\(.*\\).../\\1k cycles/"
}

bench() {
  # check if we need to initialize
  if test ! -d "${dir}/lib/amd64/" -o ! -r "${dir}/lib/amd64/fastrandombytes.o"; then
    reset_supercop_bench_dir
  fi

  for s in ${1}; do
    printf "\n\033[33mBenchmarking: >>crypto_scalarmult/%s<<\033[0m\n" "${s}"
    taskset 1 ./do-part crypto_scalarmult "${s}" >/dev/null
    cp "${datafile}" "${datafile}.${s}"
    eval_data
  done
  cat "${datafile}".* >"${datafile}"
}

[[ $1 =~ eval ]] && eval_data && exit 0
[[ $1 =~ init ]] && reset_supercop_bench_dir && exit 0

todo=${1:-curve25519 secp256k1}
for i in ${todo}; do
  bench "${i}"
done

# bench curve25519
# bench secp256k1

exit 0
