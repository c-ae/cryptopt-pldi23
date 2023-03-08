#!/usr/bin/env bash

set -e # die on error
res=bench-results.txt
pushd /root/supercop
./bench.sh | tee ${res}
printf "\n\033[32mDone.\033[0m. See above benchmark (or %s)\n" "${res}"
