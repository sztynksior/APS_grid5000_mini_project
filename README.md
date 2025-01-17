# APS_grid5000_mini_project
This is my mini project for Advanced Parallel Systems course at Universite Grenoble Alpes. 
### Goal
Main goal of this project was to understand how to work on Grid 5000 platform which is s a large-scale and flexible testbed for experiment-driven research in all areas of computer science, with a focus on parallel and distributed computing including Cloud, HPC and Big Data and AI ([source][1]). Paper [PARALLEL GENETIC ALGORITHMS (PGAs): MASTER SLAVE
PARADIGM APPROACH USING MPI][2] inspired me to implement genetic algorithm that use master slave paradigm on the platform Grid 5000.

### Gird 5000
The most challenging part of working with the Grid 5000 platform for me was reading its extensive documentation to find all the necessary information for my task and understand the hardware limitations of each cluster. I decided to work on the Grenoble Dahu cluster, whose nodes are equipped with two processors, each having 16 cores. The commands I used:
- I modified my .ssh/config file to enable direct connections to Grid 5000 sites using: ```ssh grenoble.g5k```
```
Host g5k
  User sszedel
  Hostname access.grid5000.fr  
  ForwardAgent no

Host *.g5k
  User sszedel
  ProxyCommand ssh g5k -W "$(basename %h .g5k):%p"
  ForwardAgent no
```
- To reserve resources on the Grenoble Dahu cluster and work with them interactively, I used: `oarsub -I -p dahu -l host=1`
- To see information about my jobs: oarstat -u
- To free the resources: `oardel [job id]`
- To copy files from site to a specific node (e.g., on the Dahu cluster), I used: `scp /path/to/my/file dahu-22:/path/to/dir/`
- ISince Dahu cluster use Omni-Path network, I needed to use following command to run MPI programs: `mpirun -machinefile $OAR_NODEFILE -mca mtl psm2 -mca pml ^ucx,ofi -mca btl ^ofi,openib /path/to/executable`

The Grid 5000 platform's site frontends provide many useful libraries and tools, such as tmux, git, make, and OpenMPI, which are already installed and configured. Once I understood the basic commands specific to Grid 5000, it was relatively easy to get started. 

### Genetic algorithms
Genetic algorithms (GAs) are a family of heuristic optimization algorithms. They mimic evolutionary mechanisms by representing solutions to a problem as individuals in a population and applying evolutionary operations to create a new, improved population. The evolutionary operations include evaluating and calculating the fitness function of each individual, selecting the best individuals, performing crossover, and introducing mutations. 

### PGAPack library
GAPack is a C and Fortran library that provides a collection of functions, structures, and types, forming a flexible tool for implementing various types of evolutionary algorithms. My main reason for choosing this library was its native support for MPI and the parallel model it implements.

To utilize the basic functionality of PGAPack (as was the case in this project) with MPI, only minimal explicit MPI code is required. All message passing between processes is handled implicitly by the PGARun() function, which executes the genetic algorithm using both default and user-specified parameters.

PGAPack follows the MIMD (Multiple Instructions Multiple Data) model, which is well-suited to the Grid 5000 platform. Furthermore, the library employs a controller/responder paradigm, where the controller is a single process responsible for selection, mutation, crossover, and the calculation of the fitness function. Responders are assigned parts of the population, evaluate each individual, and send the results back to the controller. This mechanism aligns closely with the approach described in the paper[PARALLEL GENETIC ALGORITHMS (PGAs): MASTER SLAVEPARADIGM APPROACH USING MPI][2].

### Maxbit problem
To test the Grid 5000 platform and the PGAPack library, I chose and slightly modified one of the example codes available on the [PGAPack GitHub repository][4]. This code implements a genetic algorithm to solve the Maxbit problem. The goal of this GA program is to maximize the number of ones in a string of bits.

### Performed tests
To test PGAPack's native support for MPI and the master/slave (controller/responder) paradigm, I ran the example GA program with the following parameters:
- Population size: 10,000
- String (gene) length: 10,000

I tested the program using 1 and 32 processes on a single host and 64, 96, and 128 processes on two, three, and four hosts, respectively. I measured the number of iterations and the fitness value of the best individual after 10 minutes.

### Tests results
The following diagram shows that the master/slave paradigm is not very scalable. Adding more than 32 processes does not have a significant impact on performance. For 124 processes, the performance gain was approximately x1.16, while the resource usage increased by x4 compared to running the GA with 32 processes.

![image](https://github.com/user-attachments/assets/a7188870-70f0-4c92-9503-1891e467a829)

The fitness of the best individual is tightly coupled with the number of GA algorithm iterations, providing no new conclusions about the tests. Therefore, I will not present them.


### Conclusion
The GA master/slave paradigm achieves the best performance per resource usage gain when used with a smaller number of processes, making it unsuitable for implementing GAs on large distributed systems. TThe PGAPack library aslo offers more advanced features that provide greater control over message passing, enabling the implementation of more scalable GA algorithms.

The Grid 5000 platform is easy to get started with but challenging to master. It offers users extensive control over the environment in which they run their experiments, along with access to a large number of nodes featuring diverse hardware and architectures. However, for simpler tasks, it provides all the necessary tools, requiring only a few key commands to execute experiments effectively.

### Tools used to make this README
English spelling correction - [ChatGPT](https://chatgpt.com/)

Diagrams - [tutorialspoint](https://www.tutorialspoint.com/execute_matplotlib_online.php)

[1]:https://www.grid5000.fr/w/Grid5000:Home
[2]:https://www.researchgate.net/publication/4102242_Parallel_Genetic_Algorithms_PGAs_Master_slave_paradigm_approach_using_MPI
[3]:https://pgapack.readthedocs.io/en/latest/about.html
[4]:https://github.com/schlatterbeck/pgapack
