# vim: set syntax=Dockerfile:
FROM ubuntu:jammy
# jammy is Ubuntu 22.10 LTS

RUN apt update && apt upgrade -y
# installing dependencies

ENV TZ=UTC
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# general deps, fiat deps, cryptopt deps
RUN apt install -y git make vim emacs nano tar zsh calc\
        coq jq libcoq-ocaml-dev make ocaml-findlib \
        autoconf clang curl g++ gcc gnuplot-nox libtool nasm pkg-config poppler-utils tmux
RUN printf "set -o vi\nalias ll=ls -l" >> ~/.bashrc

# copy and install assemblyline
COPY assemblyline-1.3.2 /root/assemblyline-1.3.2
RUN cd /root/assemblyline-1.3.2 && ./configure && \
        make CFLAGS=-O3 all install && \
        ldconfig

# get and install fiat-crypto
COPY fiat-crypto /root/fiat-crypto
RUN make standalone-ocaml -j2 -C /root/fiat-crypto

# copy and initialize SUPERCOP
COPY supercop /root/supercop
RUN cd /root/supercop && \
        ./bench.sh init

# copy and install CryptOpt
COPY CryptOpt /root/CryptOpt
RUN make all -C /root/CryptOpt && \
        make install-zsh -C /root/CryptOpt

# get latest version of Fiat-Binaries
RUN cd /root/CryptOpt/src/bridge/fiat-bridge/data && cp \
        /root/fiat-crypto/src/ExtractionOCaml/unsaturated_solinas \
        /root/fiat-crypto/src/ExtractionOCaml/saturated_solinas \
        /root/fiat-crypto/src/ExtractionOCaml/word_by_word_montgomery \
        /root/fiat-crypto/src/ExtractionOCaml/dettman_multiplication \
        . && sha256sum \
        word_by_word_montgomery unsaturated_solinas saturated_solinas dettman_multiplication > ./sha256sums

# run the CryptOpt tests
RUN make check -C /root/CryptOpt

WORKDIR /root/CryptOpt
