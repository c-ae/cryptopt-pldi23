# CryptOpt Artifact Evaluation - Getting Started (max. 30min)

1. Have a Linux machine with Docker installed. Help for installing docker [here, Install Docker](https://docs.docker.com/get-docker) or [here, Install Docker Engine  Ubuntu](https://docs.docker.com/engine/install/ubuntu/).
    - *Note*: See [TROUBLESHOOTING.md](./TROUBLESHOOTING.md) if you are using `snap.io` to install Docker and have permission errors while copying result files.

1. Get this archive and consider the directory containing this `README.md` as the root directory.

1. Build the 'quick start' image with `docker build . -t cryptopt.quick -f Dockerfile.quick`. (`.` is the *build context*. It's the path containing the `Dockerfile{,.quick}`s)
    - *Note:* This step needs an Internet connection and may take some time to download the layers.

1. Wait for the image to be built.
    - *Note:* Depending on your docker version, you may see a lot of output, some may be red. Those are hopefully just warnings on stderr inside the build, which emits red while building the container. If it still does something, it is probably okay.
    - The build was successful if it ends with `Sucessfully tagged cryptopt.quick:latest` (or `naming to docker.io/library/cryptopt.quick`, in Docker Version 23+; depending on your docker version).
    - The build command will create a container image tagged `cryptopt.quick`, where all the dependencies are installed and the projects are built, ready to go.

1. Create and run a container from this image with `docker run -ti --name CryptOpt.quick cryptopt.quick zsh` -> you are now in the built project, your terminal should change to something like `abcdef1234#`
    - *Note*: See [TROUBLESHOOTING.md](./TROUBLESHOOTING.md) if you get an error that the name `CryptOpt` already exists, or if you've accidentally dicsonnected (CTRL+C) from the container

1. Run a quick optimization inside the container by executing `./CryptOpt`. The output should be a quite colorful output of 9 blocks with 10 lines each (rather quick) followed by a (slightly longer running) 10th block. Something similar to 
    ```
    Start on brg/symbolname>>fiat/fiat_curve25519_carry_square<< >>with proofing correct<< on cpu >>11th Gen Intel(R) Core(TM) i7-11700KF @ 3.60GHz<< writing results to>>/root/CryptOpt/results<< with seed >>3283432609006676<< for >>  200<< evaluations against CC>>gcc -march=native -mtune=native -O3<< with cycle goal>>10000<< for each measurement on host>>9c181e7e0aa5<< with pid>>14122<< starting @>>2015-10-21T07:28:00.000<<
    
    fiat_curve25519_carry_square| 1/10| 20|bs  277|#inst: 139|cyclΔ      6|G  33 cycl σ  0|B  33 cycl σ  0|L  36|l/g 1.0957|D |P[  -1/  13/  13/  -1]|D[AR/ 14/ 31/ 59]| 10.0( 5%)many/s
    fiat_curve25519_carry_square| 1/10| 21|bs  277|#inst: 141|cyclΔ     32|G  33 cycl σ  0|B  33 cycl σ  0|L  36|l/g 1.0983| P|P[  -8/   4/  36/  -6]|D[MU/ 54/ 30/ 59]| 20.0(10%)many/s
    fiat_curve25519_carry_square| 1/10| 21|bs  273|#inst: 141|cyclΔ     16|G  33 cycl σ  1|B  33 cycl σ  0|L  37|l/g 1.0999| P|P[   0/   3/  53/   2]|D[MU/ 56/ 30/ 59]| 30.0(15%)many/s
    ```

    This step is successful if it ends with something like: 
    ```
    Done Success. 1985-10-26T01:22:00.000Z
     
    Wrote RES/fiat/fiat_curve25519_carry_square/seed0001677743985949.json exiting.
    ```
    
1. You can delete the quick start container now with `docker rm CryptOpt.quick`
