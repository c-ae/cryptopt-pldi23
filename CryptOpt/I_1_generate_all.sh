#!/usr/bin/env bash

set -e # die on error

echo "Generating multiply and square for all curves. Please keep the machines' noise at a minimum."
# this is for the user to read the above.
for s in {5..1}; do
  echo "${s}..."
  sleep 1
done

FS=' ' read -ra curves <<<"curve25519 secp256k1 poly1305 p256 p384 p224 p434 p448_solinas p521"
for curve in "${curves[@]}"; do
  for method in square mul; do

    # If you have multiple cores, and don't care about the screen outputs, then feel free to run in parallel by putting  an & at the end and a 'wait' before the count=
    ./CryptOpt --evals=10k --bets=5 --curve "${curve}" --method "${method}"
  done
done
count=$(find ./results/fiat/ -name 'seed*_ratio*.asm' | wc -l)
printf "\n\033[32mDone.\nGenerated %d assembly-files.\nFind all the results in ./results/fiat/fiat_*/seed*.{asm,pdf,json,dat}\033[0m\n" "${count}"
