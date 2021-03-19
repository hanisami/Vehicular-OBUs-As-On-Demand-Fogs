# Vehicular-OBUs-As-On-Demand-Fogs (Evolutionary Memetic Algorithm)

The repository contains the code for running the experiments of the evolutionary memetic algorithm of the paper [Vehicular-OBUs-As-On-Demand-Fogs: Resource and Context Aware Deployment of Containerized Micro-Services](https://ieeexplore.ieee.org/document/9032323). This paper was published in IEEE/ACM Transactions on Networking (Volume: 28, Issue: 2, April 2020).

# Usage

## Launch

To launch, run the following commands:
```bash
make all
./cpp
```
## Clean

For removing the compiled files, run the following command:
```bash
make clean
```

## Input

4x6.vcp is the input file that contains the features of four vehicles and six containers. Feel free to create your own and test with it.

Vehicle features are:
CPU, Memory, Disk, Time Available, Position at t, Position at t+1.

Micro-Service / Container features are:
CPU, Memory, Disk, Service ID.

## Output

The output is generated in the results folder

## Cite

If you found our paper useful, please consider citing it:
```bash
@article{sami2020vehicular,
  title={Vehicular-OBUs-as-on-demand-fogs: Resource and context aware deployment of containerized micro-services},
  author={Sami, Hani and Mourad, Azzam and El-Hajj, Wassim},
  journal={IEEE/ACM Transactions on Networking},
  volume={28},
  number={2},
  pages={778--790},
  year={2020},
  publisher={IEEE}
}
```
