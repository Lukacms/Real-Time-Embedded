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
**But** there are some challenges: hardware design process, varification problems, time-consuming design space exploration during DNN deployment

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
* to demonstrate hardware efficacity, adopt accelerator with proposed CE & accelerate != quantized versions of Alexnet using embedded platform named ZC706
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
End to end automation framework that can tranform DNN designs from deep learning frameworks to highly optimized hardware deployment on FPGAs
####  End-to-end automation flow
* DNNBuilder produces DNN accelerators in 3 steps (Design, Generation & Execution)
    * design: DNN is designed and trained using deep learning framework (employ CPU and GPU). The proposed flow supports hybrid quantization schemes. In this step, the feedback function provides hardware metric estimations, so that users can update their network design if not efficient enough. After training, network definition files and trained parameters are passed to the next step
    * generation: network parsing is launched to decompose the input models. The different network layers are mapped to the basic building blocks of the generated accelerator; and automated optimization provides confiuration guidlines to achieve maximum performance. Code is then generated for FPGA-based instances
    * execution: the DNN accelerator is instantiated in FPGA with unified interface, it is then concluded ready for eventual deployment
#### Architecture novelties
* To deliver high throughput performance and promising real-time response, a fine-grained layer-based pipeline is used in place of a conventionnal pipeline. It reduces latency (9.92ms vs 411.99ms) while using the same number of layers.
* To reduce on-chip memory utilization during DNN interference, a column-based cache scheme is used, as it also supports high-definition image input for resource-constrained embedded systems. It can reduce 43 times on-chip memory usage compared to the accelerator without this technology
#### state-of-the-art performance
* The designs are demonstrated by accelerating popular AI workloads on an embedded platform, and the DNNBuilder reaches the best performance and power efficiency, even without using batch processing

### PyLog: A python-based FPGA programming flow
There are problems because of the fast-growing complexity of new applications for computing systems. HLS (High-level Synthesis) can be a solution to spend less time compiling. It compiles design inputs written in high-level languages to hardware descriptions in RTL
#### PyLog flow overview
* PyLog is a python-based high level programming flow for FPGAs that presents a unified programming model for host and accelerator logic with consistent python syntax and logic.
* Most of the code can be interpreted by the standard python interpreter, except for the FPGA kernel function, decorated with `@pylog`, which call the PyLog compiler to compile the kernel function to HLS C code, to be then compiled into efficient FPGA IPs with HLS flow. The rest of the program is interpreted by the standard python interpreter running on CPU, and will become the host program of the accelerator system.
#### PyLog features
* high-level operators: allow user to express computation patterns at high level and enable better compiler; some of theses are vector additions, inner product, or even square matric multiplication. Not only simplifying programming for the users, they also pass more information or computation to the compiler compared to c/c++ programming
* type interference and type checking: not implemented natively, type checking is critical in PyLog since the same operator can have a totally different meaning when applied to different types or shapes. Thanks to the checking, the users don't have to provide explicit types annotations in their programs
* compiler optimization: that improve the design quality of generated accelerators. PyLog uses its own intermediate representation for the input code that the code analysis and transformation pass through to perform a sequence of optimizations
#### PyLog evaluation results
* expressiveness: it needs around 30% of the code length of HLS C; pylog provides good expressiveness compared to HLS C and allow user to describe the computation with fewer lines of code
* accelerator performance: after using a real-world benchmark to evaluate the performance of the generated accelerators, we see that they achieve around 3.17 times and 1.24 times speedup over CPU baseline and manually optimized accelerators

## Efficient optimizations
Three techniques: hardware-aware NAS, FPGA/DNN co-design and a unified differentiable co-design approach, accross different platforms
### Overview of hardware-aware neutral architecture search (NAS)
* NAS is the automated process of neural architectural design; it produces many state-of-the-art network, and require three components:
    * search space: includes all possible network architectures that follow a defined template
    * search algorithm: can greatly influence the efficiency of the search and the effectiveness of the final network architecture. The searchs can be supernet-based and sampling-based
    * network evaluation: is the key for efficient NAS, as fast evaluation is required to estimate the quality of individual networks. It can be prohibitively expensive due to network training, so various approaches have been proposed to expedite the evaluation (few and one-shot training)
### HW-aware NAS formulation
* with the need of deploying power-hungry DNNs into resource constrained devices, hardware-aware NAS seems to be one of the most promising techniques
    * great amount of work that adopt a specific hardware (CPU, GPU, ...) and requires different hardware-cost metric
* EDD (Efficient Differentiable DNN) provide more integrated co-optimization solutions by fusing the design space of DNN architecture and hardware accelerator
* OFA (One For All) proposes an elastic training scheme for the supernet, which allow to directly search high-accuracy architectures by selecting from the OFA network without additionnal training
### FPGA/DNN co-design
* the concept of accelerator and DNN co-design was first proposed by Hao and Cheng in «Deep Neural Network Model and FPGA Accelerator Co-design: Opportunities and Challenges»
* later on, a FPGA/DNN co-design framework was implemented, with a hardware-oriented bottom-up DNN model design (Auto-DNN), and a DNN-driven top-down FPGA accelerator design (Auto-HLS)
#### The key to co-design: Bundle
* executing both Auto-DNN and Auto-HLS is made by proposing basic building blocks called *Bundles* that can be used to build both of them
* a DNN can be constructed by replicating a bundle for a certain number of layers with pooling layers inserted
* an accelerator may be constructed by building a hardware module for the certain module, and then reusing it for others, which significantly reduces resource usage with resource sharing
#### Progressively reducing search space
* selecting an optimal bundle is non trival given the large design space and long DNN training time, so the search space must be narrowed as early as possible
* filtering out unfavorable bundles at early stage
* on the first step, some analytical models for the overall DNN resource utilization and latency are made
* on the second, the bundles are evaluated and selected by being replicated *n* times to build a DNN and train for a small number of epochs. The bundles on the pareto curve (set of efficient solutions) are kept for the next step
* the third step consists of building a DNN using bundles and training it after selecting the top-n promising bundles candidates. DNN candidates are created and updated for each bundle candidate until the latency target is met, and then perturbated by changing the number of bundle replications, down-sampling configuration between bundles and channel expansion confiuration to find the DNN architecture which meets the performance constraints with the highest accuracy.
* compared to the 1-st place winner of the FPGA category, there is 6.2% higher IoU (Intersection over Union), 40% lower power and 2.5 times better energy efficiency
### EDD: Efficient Differential DNN Architecture Search
* on top of the previous design, EDD is a more generalized and unified approach. EDD is a fully simultaneous, efficient differentiable DNN architecture and implementation co-search methodology
#### Fused co-design space
* the key is to fuse the design space of DNN architecture search and hardware implementation search. To carry out both DNN architecture and hardware accelerator co-search, the loss function has to be minimized ($min: L = Acc_{loss}(A, I).PerF_{loss}(I) + \beta . C^{RES(I)-RES_{ub}}$), with $Acc_{loss}$ being the DNN accuracy loss, $Perf_{loss}$ the hardware performance loss, $RES$ the resource utilization and $RES_{ub}$ the resource upper bound.
* in the search space, each DNN is composed of *N* building blocks, that have *M* candidate operations in every one of them. The outputs of each block is calculated from the outputs of its *M* candidate operation, with the adoption of the Gumbel-Softmax funcion where each operation $op_m^i$ will be sampled for a sampling parameter following the law's distribution which convert discrete non-differenciable sampling to continuous differenciable sampling. They form a complete DNN that can be evaluated for accuracy and implementation performance
* $A$ is the activation output of layer $I$ that is the input
* The implementation search space is formed but letting each $op_m^i$ have its own omplementation variables (quantization $q$, accelerator parallelism, loop tiling factor, ...)
#### Differentiable performance and resource formulation
* the loss function differenciable has to be formulated with respect to search space $A$ and $I$. By decending this loss function on the validation set, ${A,I}$ can be learned simultaneously
#### State-of-the-art results
* the results are demonstrated on a subset of ImageNet dataset randomly sampled from 100 classes, and target 3 hardware architectures that each have a search DNN model (EDD-Net) where a single processing element is reused by all layers. Each model is produced through EDD withing a 12-hour search on a P100 GPU
* EDD-Net-1 reaches similar or better accuracy comparing with the state-of-the-art DNN models and other NAS while achieving the shortest interference latency
* EDD-Net-2 delivers the shortest latency on FPGA among all the DNNs
* EDD-Net-3 achieves higher throughput with a much higher accuracy comparing with the state-of-the-art (40.2 fps vs 27.7 fps for 7.7% and 10.0% top-5 error)

## Conclusion
* the high computation, memory demand, and diverse application-specific requirements make developping DNN-based AI applications challenging.
* Efficient machine learning algorithms, accelerator and compiler design, and various co-design and optimization strategies are methods to overcome theses challenges.
* they believe that embedded AI solutions will involve more effective and comprehensive design methods in the future, as their AI algorithms designs (ELB-NN and VecQ) can adopt more advanced quantization scheme to minimize network compression loss
* future works will considerate more diverse network architecture and layer-wise data distribution; extend DNNBuilder and PyLog to create framework and tools for hardware design, synthesis and workload compilation for a smoother accelerator design process
