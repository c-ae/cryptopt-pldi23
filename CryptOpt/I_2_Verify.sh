#!/usr/bin/env bash

set -e # die on error

# Parameter 1 must be the asm file

# If you place this script into your $PATH, change this variable to
# where CryptOpt has been unpacked to
INSTALLDIR="$(dirname "${0}")"

# go into the Install directory. Everything is relative from there
cd "${INSTALLDIR}"

if [[ ${#} -ne 1 ]]; then
  echo "Please call this function with one parameter" >&2
  exit 1
fi

if [[ ! -f ${1} ]]; then
  printf ">>%s<< does not deem to be a valid file.\n" "${1}" >&2
  exit 1
fi

gen_verify_cmd() {
  PATH="$(realpath ./bins/node/bin):${PATH}" \
    /usr/bin/env node \
    "./dist/VerifyCommand.js" "${1}"
}

cmd="time $(gen_verify_cmd "${1}")"

read -r -p $'Do you want to execute the following command [y/N]?\x0a'"${cmd}"$'\x0a' input

case $input in
[yY][eE][sS] | [yY])
  echo "Yes... Proceeding"
  ;;
[nN][oO] | [nN])
  echo "No, okay :("
  exit 0
  ;;
*)
  echo "Invalid input..."
  exit 1
  ;;
esac

if bash -c "time ${cmd}"; then
  printf "\033[32mDone. Equivalence check succeeded.\033[0m\n"
else
  printf "\033[31mDone. Equivalence check did not succeeded. The given Assembly does not implement the function correctly\033[0m\n"
fi
