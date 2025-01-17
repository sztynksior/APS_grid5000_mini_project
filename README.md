# APS_grid5000_mini_project
This is my mini project for Advanced Parallel Systems course at Universite Grenoble Alpes. 
### Goal
Main goal of this project was to understand how to work on Grid 5000 platform which is s a large-scale and flexible testbed for experiment-driven research in all areas of computer science, with a focus on parallel and distributed computing including Cloud, HPC and Big Data and AI ([source][1]). Paper [PARALLEL GENETIC ALGORITHMS (PGAs): MASTER SLAVE
PARADIGM APPROACH USING MPI][2] inspired me to implement genetic algorithm that use master slave paradigm on the platform Grid 5000.

### Gird 5000
Working on platform Grid 5000 is relatively easy, it is very user freindly but main challange to start working on it was to read its vast documentation in order to find all the needed information for my task.
Used commands:
- I modified my .ssh/config file to be able to directly connect to grid 5000 sites using for example: ```ssh grenoble.g5k```
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
- To reserve resources at Grenoble dahu cluster and work with them interactively I used: `oarsub -I -p dahu -l host=1`
- To see information about my jobs: oarstat -u
- To free the resources: `oardel [job id]`
- To copy files to the node (for example at dahu cluster) that I am using: `scp /path/to/my/file dahu-22:/path/to/dir/`
- I was working on dahu cluster which use omni-path network, becouse of that I needed to use following comand to run mpi program: `mpirun -machinefile $OAR_NODEFILE -mca mtl psm2 -mca pml ^ucx,ofi -mca btl ^ofi,openib /path/to/executable` 
 
[1]:https://www.grid5000.fr/w/Grid5000:Home
[2]:https://www.researchgate.net/publication/4102242_Parallel_Genetic_Algorithms_PGAs_Master_slave_paradigm_approach_using_MPI

