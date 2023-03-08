# Claims

We will quickly list the claims supported and claims not (fully) supported.
Then, we will describe step-by-step instructions to verify the supported claims and describe how the not (fully) supported claims can be spot tested.

## Claims fully supported by the artifact

- I.   Running an optimization will generate verified high performance assembly code for 18 cryptographic primitives in total (Fiat Cryptography-based).
- II.  Running an optimization on `bitcoin-core`'s `secp256k1` will generate high performance assembly code for multiply and square (without symbolic correctness checks)
- III. Performance over time increases during the optimization, generating a graph (c.f. Figure 9. In the [Paper appendix](./pldi2023-paper326-supplemental_text.pdf))
- IV.  Performance of the generated code is typically faster than `clang/gcc's -O3 -march=native -mtune=native` options (c.f. Table 6. In the [Paper appendix](./pldi2023-paper326-supplemental_text.pdf))
- V.   Performance of the generated code plugged in into SUPERCOP's benchmarking tools shows speedup in scalar multiplication (c.f. Table 7. In the [Paper appendix](././pldi2023-paper326-supplemental_text.pdf))

## Claims not (fully) supported by the artifact

- VI. Performance of the generated code on one platform is typically faster generated on other platforms. (Entirety of Table 6)

# Step-by-Step Instructions

## General Setup

1. Build the full image with `docker build . -t cryptopt` from the root directory (the one containing the `Dockerfile`) ()
    - *Note*: This takes a bit longer (55min), because we also re-build everything proof-related from source.
    - The build was successful if it ends with  `naming to docker.io/library/cryptopt` (or `Sucessfully tagged cryptopt.quick:latest` depending on your docker version).

1. Once docker succeeds, create and run a container from this new image with `docker run -ti --name CryptOpt cryptopt zsh` just like in the 'Getting Started' phase.
    - *Note*: From now on, unless otherwise noted, everything is considered from inside the container (as opposed to from the 'host system').

The entry point to generate assembly is always the `./CryptOpt` script. `./CryptOpt --help` gives an overview of options, tab completion should work and should give the options like `--betRatio` until `--version`

While optimizing the user is updated with status lines.
The exact meaning of all those details is not too important for the artifact evaluation.
The most important ones are the first field, which sates the primitive being optimized, the middle, 'l/g x.yyyy' value showing the ratio over ots compilers and the last second to last field, stating how far in the current run the optimization is.
More details in [CryptOpt's README](./CryptOpt/Readme.md).

**Important Note**: Most of the following are performance benchmarks.
Due to the nature of those, the numbers are most likely not the exact same.
Please take architectural differences, system noise and randomness into account.
If possible it may be good to disable boosting behaviour, fix the CPU frequency and provide adequate cooling on the host system.
(on the host system, `# sudo ./CryptOpt/modules/scripts/misc/set_frequency.sh fix` attempts to quiet the system by setting the frequency to a minimum, disabling the boosting and setting the governor to `performance`, `# sudo ./CryptOpt/modules/scripts/misc/set_frequency.sh default` will reset to *our* defaults.)

Additionally, better results can usually be achieved using the Performance Counters (PMC) over the time stamp counters `rdtscp`.
To enable them, run `echo 1 | sudo tee /proc/sys/kernel/perf_event_paranoid` on the host system.

## Generate 18 verified primitives (Claim I)

### Context 

The paper claims to be able to generate code for multiply and square primitives of nine fields (c.f. Section 5.3). And that those are verified.

### Action

`./CryptOpt --curve XXX --method YYY` will call Fiat Cryptography internally, generate assembly, write them into `./results/fiat/<<PRIMITIVE>>` and prove them correct.
Either choose the combination curve/method you like to generate or use the script `./I_1_generate_all.sh` to generate all. (1.5 hours)
This may take a bit and does not need user interaction (), but you'll see the status output on the screen.
This is successful if it generated 108 assembly files (18 primitives with each 5 bets plus 1 final run) and ends with 

    Done.
    Generated 108 assembly-files.
    Find all the results in ./results/fiat/fiat_\*/seed\*.{asm,pdf,json,dat}

1. Once the assembly is generated we can double check to make sure they are verified.
    - Choose an implementation that we want to verify and copy it somewhere convenient: e.g. `cp ./results/fiat/fiat_curve25519_carry_mul/seed000*_ratio*.asm /tmp/generated.asm`.
    - Execute `./I_2_Verify.sh` with the file as a parameter:`./I_2_Verify.sh /tmp/generated.asm`
    This will generate the proof command, which you can confirm (press 'y' + Enter) to execute.
    During the proof, Fiat Cryptography will generate the Fiat IR for the given field, and check equivalence against the assembly.
    It will proof or disproof the correctness.

1. Now, change the generated assembly such that the semantics are preserved and try again: E.g. 
    The file may contain an instruction like `lea r8, [rdx + 2 * rcx]`.
    Replace those with the following two instructions `lea r8, [rcx + rcx]`, `lea r8, [r8 + rdx]`. (The container has `vim`,`emacs` and `nano` installed)
    Then, executing `./I_2_Verify.sh /tmp/generated.asm` should yield that it is still valid. 

1. Now, lets change the generated assembly such that the semantics are **not** preserved and try again: E.g. 
    The file may contain an instruction like `lea r8, [rdx + 2 * rcx]`.
    Now change that `2` to a `4`: `lea r8, [rdx + 4 * rcx]`
    Executing `./I_2_Verify.sh /tmp/generated.asm` on this file should yield that it is **not** valid.
    It additionally will print the error, of where it failed to prove equivalence.

1. The `./I_2_Verify.sh` script will run the verification command through `time`, such that for every invocation it shows how long it took.
    Find one assembly from each primitive, verify it and note the time it took.

### Evaluation

This claim is successfully validated,
1. if CryptOpt generated assembly code for all 18 primitives,
1. if both versions, the initial version and the version containing the semantics preserving change are verified as 'correct',
1. if the invalid version is rejected by the proof engine and
1. if the time it takes to validate the code is in the same order of magnitude as the verification times claimed in Table 3 for the chosen primitive.
    - *Note*: The numbers in the table are averaged over our eight machines, individual times may change slightly, and
    - taken from our most performant solution. If the assembly is considerably longer than the ones reported in Table 2 (also averaged over the eight machines), the verification time may also increase.


## Generate primitives for Bitcoin-Core (Claim II)

### Context

The original `bitcoin-core` files can be found in  `./src/bridge/bitcoin-core-bridge/field_5x52_int128_impl.h`. We convert this into `field.c`, `field.ll` and finally to `field.json`.
In a nut shell, this is tedious `sed` scripting and `llvm` parsing (the output of which is very version dependent.).We supply the converted files already, so no action must be taken here.

### Action

1. Generate assembly code for `bitcoin-core` by executing `./CryptOpt --bridge=bitcoin-core --curve=secp256k1 --method=mul` and `./CryptOpt --bridge=bitcoin-core --curve=secp256k1 --method=square` (around 1 mins each)

### Evaluate

1. After the optimization is completed, find the optimized code in the results folder by executing `ls ./results/bitcoin-core/secp256k1_fe_{sqr,mul}_inner/seed*.asm`.
    If there is `seed<>_ratio<>.asm` files for each primitive, this claim can be considered validated (We evaluate performance during Claim V).


## Generating primitives improves over time (Claim III)

### Context

Every optimization run features a 'l/g x.yyyy' value in the status line. This is the speedup compared to the off-the-shelf compiled C code. If `x == 0` in that value, the generated code is slower than the C compiled baseline, if `x>0` then it's `x.yyyy` times faster.
CryptOpt logs this value into the `.dat` files alongside the assembly files. Additionally, we generate a `pdf` with a plot of this data.
After all the optimizations (from Claim I), we should have many optimization graphs, we just need to view them.
There is no `X` Server installed in the container, so we will copy the results folder to the host machine and view the `pdf`s from there.

### Action

1. There are many graphs already created, but if you want to be as close as possible to the one in Figure 9 in the [Paper appendix](./pldi2023-paper326-supplemental_text.pdf):
    - Execute on an Intel i7 10th Generation, in the container, `CC=clang ./CryptOpt --curve p434      --method square --evals 200k --bets=20 --betRatio=0.1` (for Fig 9.a)  and 
    - Execute on an Intel i7 11th Generation, in the container, `CC=clang ./CryptOpt --curve secp256k1 --method square --evals 200k --bets=20 --betRatio=0.1` (for Fig 9.b) (the former 4.5 hours, the latter 20 min).
1. On your host system, copy the results folder via `docker cp CryptOpt:/root/CryptOpt/results/ /tmp/`.
1. Take a pdf viewer of your choice and view the `pdf`s in `/tmp/results/fiat/fiat_poly1305_carry_mul/*.pdf` (or respective other function names in the folder)

### Evaluation

1. Please note, we have seen many different graphs being generated for different curves on different machines.
    Yours might look different with spikes (system noise), steps (boosting behaviour, thermal throttling, frequency scaling), tight or wider amplitudes (AMD vs. Intel, on some generations).
    You may want to look at a handful of graphs and then conclude.
1. If this graph looks similar to the ones in Figure 9, or at least if the speedup starts low and increases over the number of mutations then this claim can be considered as valid. 


## Generated primitives are faster then OTS compiler (Claim IV)

### Context

In the earlier experiments, we (by default) compared against `GCC`. We see the ratio against `GCC` in the `l/g` columns while optimizing and in the generated graph (the `pdf`s).
You can change the compiler (and even Compiler Flags) via the `CC` (`CFLAGS`) environment variable.

### Action

1. Re-run (some) experiments from 'Claim III' with `CC=clang ./CryptOpt --curve XXX --method YYY` or all with `CC=clang ./I_1_generate_all.sh`.
    You may want to archive the `results` folder before, because it may otherwise be tricky to distinguish the used ots compiler.
    You can do this with `mv results results.gcc`.
1. Check, if in the preface of the optimization it says `>> clang -march=native -mtune=native -O3<<` like here:

    Start on brg/symbolname>>fiat/fiat_curve25519_carry_square<< >>with proofing correct<<
    on cpu >>12th Gen Intel(R) Core(TM) i9-12900KF<< writing results to>>/root/CryptOpt/results<<
    with seed >>3536902944381312<< for >>  200<< evaluations against CC>>clang -march=native
    -mtune=native -O3<< with cycle goal>>10000<< for each measurement on host>>b172961758ab<<
    with pid>>1309<< starting @>>2023-03-08T04:01:25.598Z<<
    
### Evaluation

1. Note the `l/g` value at the end of the optimization, or check the generated `pdf`s of a certain curve / method combination.
1. Find the column of the machine that is closest to your architecture in Table 6 in the [Paper appendix](./pldi2023-paper326-supplemental_text.pdf)
1. Find the row `clang` and compare the value. If this value is too far off, you may want to check the graph whether it seems like it still optimized at the end and then try with a bigger budget `--evals 200k`.
1. Do the same with `gcc` and the previous optimization results.

## Scalar multiplication via SUPERCOP (Claim V)

### Context

To evaluate the scalar multiplication, we need to generate a handful optimized implementations for the field operations. That is:
    - Curve25519 square and multiply for the 64-bit saturated implementation and 
    - Curve25519 square and multiply for the 51-bit unsaturated version as well as
    - the verified secp256k1 multiply (dettman implementation strategy; square is not yet supported) and
    - the bitcoin-core based versions `{square,mul}_inner`.

We will then convert those results to SUPERCOP-compatible assembly files and run the SUPERCOP benchmark against the well-known implementations.

### Action

1. Execute the `./V_1_generate_for_supercop.sh` script.
    - *Note*: this will take a while, please try to keep the noise on this machine at a minimum for best results. (60 min)
    - *Note*: if this take too long for you, you can change the `--evals` parameter inside the script to something smaller.
    If you have much more time at hand, you can execute this script multiple times (even in parallel: open a second terminal on the host, run `docker exec -ti CryptOpt zsh` and you have a second prompt into the container) to get more (potentially better) results.
    In the paper we claim that we run three in parallel (Section 5.1.Generation).
    - This should have created new directories and files in the `./results/fiat/` as well as in `./result/bitcoin-core`
    (this is successful if it prints "Done. You can see the `pdf`s in ./results/{bitcoin-core,fiat}/\*/\*.pdf. You can now run the copy script. Execute ./V\_2\_copy\_results\_to\_supercop.sh")
1. Execute the `./V_2_copy_results_to_supercop.sh` script to transform the results into SUPERCOP directory and format.
    (this is successful if it prints "Done. You can run the SUPERCOP benchmark now. Execute ./V\_3\_run\_supercop\_benchmark.sh")
1. Run the benchmark `./V_3_run_supercop_benchmark.sh`.
    *Note*: will take a while (2 min).
    (this is successful if it prints "Done. See above benchmark (or bench-results.txt)")
1. This should print to the terminal (and to ./bench-results.txt for this matter) an output similar to this: (this one is from the i9 13G)
    ```
Benchmarking: >>crypto_scalarmult/curve25519<<
                        HACL* fe-64               210k cycles
              OSSL fe-64 + CryptOpt               217k cycles
              OSSL fe-51 + CryptOpt               227k cycles
                     OSSL fe-64 ots               231k cycles
                           OSSL ots               238k cycles
                     OSSL fe-51 ots               238k cycles
                           amd64-51               251k cycles
                            sandy2x               262k cycles
                           amd64-64               266k cycles
                          donna-c64               285k cycles
                              donna               495k cycles

Benchmarking: >>crypto_scalarmult/secp256k1<<
      libsecp256k1 + CryptOpt (CS2)               235k cycles
            libsecp256k1 + CryptOpt               243k cycles
                   libsecp256k1 (C)               246k cycles
                 libsecp256k1 (ASM)               253k cycles
    ```
    This list lists the fastest version for each implementation.
    The first column specifies the implementation as found in the paper's Table 7 and the second column the elapsed cycles.

1. *Note*: If those numbers deviate significantly, it may be because it was run in the Docker container and not bare metal.
    If this happens, you can try validating bare metal. (Needs Clang 14 and GCC 11.3.0 installed to be representative.)
    To validate bare metal, after executing `./V_3_run_supercop_benchmark.sh` inside the container, copy the `/root/supercop` to the host, change the `hostname` in `/root/supercop/bench/<<hostname>>/data` and run the benchmark: 
    ```bash
    docker cp CryptOpt:/root/supercop .
    cd supercop
    mv bench/* bench/`hostname | sed 's/\..*//' | tr -cd '[a-z][A-Z][0-9]' | tr '[A-Z]' '[a-z]'`
    ./bench.sh
    ```
    If even the '+CryptOpt' cycles are still not comparable, you may need to run the optimization on bare metal as well.
    For this, you'd need to
    - install `AssemblyLine` (follow the install instructions in `./assemblyline-1.3.2/README.md`#How to Use) on the host system,
    - copy the built `/root/CryptOpt` from the container to the host and regenerate the required filed with `./V_1_generate_for_supercop.sh`
    - change the paths for CryptOpt and supercop `./V_2_copy_results_to_supercop.sh` accordingly and execute it.
    - change the paths for supercop in `./V_3_run_supercop_benchmark.sh` and run the benchmark again.
    If this still does not yield similar results, you may want to `taskset` the `./CryptOpt` commands in `./V_1_generate_for_supercop` to a certain core (or HyperThread) to avoid context switches from the kernel and try again.


### Evaluation

This list is sorted by `elapsed cycles`, note the `...k cycles`.
Find the column in Table 7, that is closest to your architecture.
Then compare the ...k cycle values.

If you happen to have a very similar architecture, the numbers should be very similar, too. (May consider turning off boosting and HyperThread'ing as well as fixing the frequency).
If the absolute numbers deviate significantly (as in our case above, because we did not fix the frequency), the relative order and ratios should still match.
To check this, 
- Find the implementations with the '+CryptOpt' suffixes.
- Compare with the default ones. (i.e. `OSSL fe-64 ots` vs. `OSSL fe-64 + CryptOpt`)
- Calculate the ratio in the paper: e.g. for Intel i7 12G (the closest one to our Intel i9 13G) `412/394 = 1.045` (CryptOpt is around 4.5% faster)
- Calculate the ratio in the experiment: `231/218 = 1.059` (CryptOpt is around 5.9% faster)
 
It those are similar enough, considering architectural differences, noise and variability of performance claims in general, the claims can be approved.
Otherwise, try to optimize again (after a reboot maybe) or on a different machine, which matches the one from our experiment closer.

## Optimization is platform specific (Claim VI)

### Context

The problem here is that we cannot expect the reviewer to access to all the eight machines that we have used, nor do we expect up to 70 hours of the reviewer to observe the experiment.
If the reviewer has access to more than one machine and they are rather similar to the machines reported in Table 1 in Chapter 5,
the reviewer can evaluate samples to spot test single fields of Table 6 (Appendix C).

### Action

This could be done like this:
1. Choose a curve / method combination from Table 6.
1. Build the container on two different machines (the quick-start container suffices for this)
1. Generate assembly code for this combination on two different machines.
1. Copy the generated code to the respective other machine's CryptOpt docker container
1. Compare both with `./VI_1_Compare.sh ./path/to/foreign/file.asm ./path/to/local/file.asm`

#### Example:

1. P-224 Multiply (c.f. Table 6; P-224 sub-table; upper part)
1. I have machines 1900X (AMD) and i9 10G (Intel), on which the docker container is built and running.
    - On both systems, in the container, execute `./CryptOpt --curve p224 --method mul --evals 200k --bets=20 --betRatio=0.1`. (20 min) (Those parameters are the ones claimed by the paper in the Appendix B: `200 000` mutations in total, `20` bets, `1000` mutations each).
    - This should end with `Wrote RES/fiat/fiat_p224_mul/seed0001678143128980.json exiting`.
    - Find the generated file with `ls /root/CryptOpt/results/fiat/fiat_p224_mul/seed000*_ratio*.asm`, which should return with something like `/root/CryptOpt/results/fiat/fiat_p224_mul/seed0001678143128980_ratio24375.asm`.
1. Open another terminal on the host system, (i.e. **not** inside the container),
    - Copy the result file from the container to the host system `docker cp CryptOpt:/root/CryptOpt/results/fiat/fiat_p224_mul/seed0001678143128980_ratio24375.asm ./AMD.asm` (\*) *NOTE*: use `docker cp CryptOpt.quick: ...` if you are using the Getting-started container.
    - Do this on both systems, i.e. my 1900X and my i9 10G, changing the destination name to `Intel.asm` on the Intel machine.
    - *Note:* See [TROUBLESHOOTING.md](./TROUBLESHOOTING.md) if problems occur. 
    - You should have an `./AMD.asm` on the AMD machine, and an `./Intel.asm` on the Intel machine.
    - Transfer the `AMD.asm` file to the Intel machine and the `Intel.asm` to the AMD machine.
    - Now copy the foreign file into the container: on the AMD (host) machine execute `docker cp /path/on/host/machine/to/Intel.asm CryptOpt:/root/CryptOpt` and analogously copy `AMD.asm` on the Intel machine. (or `docker cp ... CryptOpt.quick: `)
1. Compare inside the container (on the AMD machine) with `./VI_1_Compare.sh ./Intel.asm /root/CryptOpt/results/fiat/fiat_p224_mul/seed0001678143128980_ratio24375.asm` (the second parameter here is the path to the file, which we used in the `docker cp ... AMD.asm` in last step marked with  (\*)).
    - This will execute both files and robustly collects the medians.
    - Should return with a ratio like:
    ```
    9c181e7e0aa5# ./VI_1_Compare.sh ./Intel.asm /root/CryptOpt/results/fiat/fiat_p224_mul/seed0001678143128980_ratio24375.asm
    Foreign:   19349.80 cycles (file: ./Intel.asm)
    Local:     17326.04 cycles (file: /root/CryptOpt/results/fiat/fiat_p224_mul/seed0001678143128980_ratio24375.asm)
    Ratio: Foreign / local = 19349.80 / 17326.04 = ~1.11675835909417270190
    ```

### Evaluation

Looking in Table 6, P-224, upper half, row 'i9 10G', column 1900X, it states `1.10`, which means that the paper claims that the locally optimized version (1900X) is 10% faster than the foreign version (i9 10G), because we ran on the 1900X.
Our results here show that in this run it actually is around `11.6 %` faster. You may repeat this `./VI_1_Compare.sh` command multiple times to see how consistent the results are.

Now as performance measurements always fluctuate we only expect the result to be in the range of `+- 4%`, if the exact same machines are used with the exact setup (e.g. not Dockerized, but bare metal) and the same amount of mutation settings. 
If your measurements are too far off, please consider 
- using a different machine (if you can),
- a different (maybe smaller) curve (average size of the curve is listed in Table 2), or
- use different mutation settings, more / less mutations, or
- simply run the optimization again.


