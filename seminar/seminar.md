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

### Efficient co-design optimization
* algorithm / accelerator co-design & co-search to solve the edge AI challenges
* accelerators need to provide extensive support for != DNN components without introducing too many restrictions on network design
* DNN / accelerator co-design => consider software & hardware metrics simultaneously
* neural architecture search (NAS) => successfull for DNN models
    * hardware- aware NAS aims to deliver high-accuracy models with hardware efficiency

## Efficient machine learning model designs
ML requires high inference accuracy, aggressive inference speed, throughput & energy efficiency to meet real-life demand => rely on hardware-efficient DNN

### ELB-NN
* extremly low bit-width neural network
* proposed to enhance energy efficiency when running image classification on embedded FPGA
#### Hybrid quantization scheme
* means that different quantization schemes are involved for the network's parameters and activations
    * can go all the way down to binary
* first investigate their impact on network inference accuracy
* after an analysis with AlexNet, they conclude that the network is relatively robust to the precision of parameters. On the contrary, the precision of activation impacts classification accuracy
* 80% computation increase & 3.9% accuracy improvement in new Alexnet version
* by increasing model complexity, they can bring back the accuracy
#### Hardware accelerator for ELB-NN
* parameterized computation engine (CE) to handle ELB-NN. It has a flexible support of low bit-width quantization & configurable parallelism during execution
* to demonstrate hardware efficacity, adopt accelerator with proposed CE & accelerate != quantized versions of Alexnet using embedded plateform named ZC706
    * ELB-NN can achieve throughput performance up to 10.3 TOPS => outperforms previous designs

### The VecQ
Vectorized Quantization => training quantization that is based on a novel quantization loss measurement metric called vector loss.
#### Quantization with vector loss
* we use square of euclidean distance of the date before & after quantization to represent its loss (square 2-norm / l2 distance)
* adopting l2 distance collects the loss of each quantized data individually & neglects the distribution and correlations amongs data points in kernel or layer
* with the approaches, the orientation loss show that the quantization takes 2 stages to minimize the 2 losses independantely = steering stage & driving stage
    * steering stage = adjust orientation of weight vector to minimize orientation loss
    * driving stage = fix the orientation & only scale the modulus of the vector to minimize the modulus loss
#### Framework integration
* VecQ quantization is integreated in DNN training flow for weight data & activation data
* to simplify the computing process, the weight is treated as normally distributed & an interval $\lambda$ is used regarding the given bitwidth constraint
* for the activation output of a layer (during training), we compute a distribution parameter of activation outputs & update it with exponential moving average
    * distribution parameter is employed as linear factor to activation function
* after evaluting VecQ on image classification & comparing it with state-of-the-art solutions (e.g: BWN, TWN, ...), we see that it outperforms most of the solutions with the same bitwidth config + provide wider range of coverage

## Efficient accelerator design and workload mapping
Introducing DNNBuilder and PyLog to bridge gap between fast DNN model design & hardware accelerator
### DNNBuilder
