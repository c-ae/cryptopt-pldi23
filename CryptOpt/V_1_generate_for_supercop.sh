#!/usr/bin/env bash

set -e # die on error

echo "Generating files necessary to run the SUPERCOP benchmark. Please keep the machines' noise at a minimum."
# this is for the user to read the above.
for s in {5..1}; do
  echo "${s}..."
  sleep 1
done

# those are the parameters claimed by the paper.
# you may want to change this to something smaller, if you don't have that much time at hand
# But be aware that the results than may differ

common=("--evals=200k" "--bets=20" "--betRatio=0.1")

#for curve25519/openssl-fe51-cryptopt
./CryptOpt "${common[@]}" --curve curve25519 --method=mul
./CryptOpt "${common[@]}" --curve curve25519 --method=square

#for curve25519/openssl-fe64-cryptopt
./CryptOpt "${common[@]}" --curve curve25519_solinas --method=mul
./CryptOpt "${common[@]}" --curve curve25519_solinas --method=square

#for sec256pk1/libsecp256k1-ots-cryptopt-dettman[@]
./CryptOpt "${common[@]}" --curve secp256k1_dettman --method=mul

#for sec256pk1/libsecp256k1-ots-cryptopt-bcc
./CryptOpt "${common[@]}" --bridge bitcoin-core --curve secp256k1 --method=mul
./CryptOpt "${common[@]}" --bridge bitcoin-core --curve secp256k1 --method=square

printf "\n\033[32mDone.\033[0m You can see the pdfs in ./results/{bitcoin-core,fiat}/*/*.pdf. You can now run the copy script. Execute ./V_2_copy_results_to_supercop.sh\n"
