# Compilation and Optimizations for Efficient Machine Learning on Embedded Systems

<ins>**Authors:**</ins> Xiaofan Zhang, Yao Chen, Cong Hao, Sitao Huang, Yuhong Li, Deming Chen

## Introduction
* development of Deep Neural Network (DNN) => machine learning more accessible => they become more complicated & need more resources to work / greater energy consumption / ... => difficulties for DNN dev on hardware, especially for embedded services

## Background & related work
### Efficient DNN Design
* they have millions of parameters, billions of operations
* focus on network compression to reduce network complexities & lower compute and memory demands => use quantized data to represent float params
* network pruning, to reduce redundancy of DNN structures => benefits come from fully-connected (FC) layers => more sophisticated algorithms are required as time pass for pruning

### Efficient accelerator design & DNN mapping methods
* build domain-specific hardware
* acceleration libraries on CPU
* kernel optimization on GPU
* customized accelerators on FPGA & ASICS
**But** there are some challenges: hardware design process, varification problems, time-consuming design space exploration during DNN deployement
