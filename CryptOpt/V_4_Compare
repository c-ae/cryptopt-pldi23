#!/usr/bin/env bash

# die on error
set -e

# If you place this script into your $PATH, change this variable to
# where CryptOpt has been unpacked to
INSTALLDIR="$(dirname "${0}")"

# go into the Install directory. Everything is relative from there
pushd "${INSTALLDIR}" >/dev/null

if [[ ${#} -ne 2 ]]; then
  echo "Call with exactly two asm files ${0} ./path/to/foreign.asm ./path/to/local.asm" >&2
  exit 1
fi

#run
foreign=$(
  PATH="$(realpath ./bins/node/bin):${PATH}" \
    /usr/bin/env node \
    "./dist/CountCycle.js" "${1}" |
    awk '{print $1}'
)
loc=$(
  PATH="$(realpath ./bins/node/bin):${PATH}" \
    /usr/bin/env node \
    "./dist/CountCycle.js" "${2}" |
    awk '{print $1}'
)
printf "Foreign:   %7.2f cycles (file: %s)\n" "${foreign}" "${1}"
printf "Local:     %7.2f cycles (file: %s)\n" "${loc}" "${2}"
printf "Ratio: Foreign / local = %7.2f / %7.2f = %s\n" "${foreign}" "${loc}" "$(calc "${foreign}" / "${loc}")"
