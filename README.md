# Multicore In-Memory BFS on Labeled Graphs


README

This repository contains code for CS6284 Final Project on Multicore In-Memory BFS on Labeled Graphs

<h1>Requirement</h1>

The code needs to be compiled and run on Linux platform with gcc version of 5.0 and above.

The gcc compiler needs to support Cilk Plus. As gcc have full support for Cilk Plus since version 5.0, this should not be an issue.

<h1>Compilation</h1>

To compile the code, enter the repository and run command <code> make </code>. 

<h1>Input</h1>

The input file is a graph dataset encoded as a binary file. 

Such input file can be generated in the following steps:

1. Enter repository

2. Enter command <code> dataGen/PaRMAT/Release/PaRMAT -nVertices [no. of vertices] -nEdges [no. of edges]</code>, where [no. of vertices] and [no. of edges] are integer values to be filled in. 

This command generates a text file named <strong>out.txt</strong> with the specified number of vertices and number of labels.

3. Enter command <code>dataGen/addnLabelsByProbability.py out.txt [no. of labels] [p1] [p2] ...</code>, where [no. of labels] is an integer value indicating the number of labels to be put in the graph, and [p1], [p2], ..., [pn], are float values indicating the probability of having the 1st, 2nd, ..., nth label. 

This command generates a text file named <strong>out</strong> with edge data from <strong>out.txt</strong> and additional labeled data

<h1>Running the code</h1>

To run the code you need to call the corresponding algorithm binary with a number of required options:

<b>./algorithm_binary –n #_of_vertices –m load_mode –f path_to_graph [optional parameters].</b>

When not running the NUMA-aware version, it is recommended to use <b>numactl --interlave=all</b> before the command line to improve performance. <br/>
To change the number of threads running, it is necessary to edit the constants ALGO_NB_THREADS and CONCURRENCY_THREADS in random.h.


<h1>Pre-processing</h1>

The graph can be represented as:

1.	An edge array
2.	Adjacency lists
3.	2D grid

The way these data layouts are created can be varied: Using a radix sort, a dynamic allocation and reallocation on load or count sort. 
The implementation of all of these options is in <b>init_all.c</b>. The data layout can be selected by setting the <b>load_mode</b> flag. 

If the algorithm needs to be run an undirected graph, pass the <b>–u</b> flag when running the algorithm. If the graph is already undirected and the algorithm requires creating incoming adjacency lists, passing <b>–s 1</b> will disable this. 


<h1>NUMA-Aware data placement</h1>

The additional pre-processing step needed to place data in a NUMA-Aware manner is implemented in the actual files that run the algorithms with NUMA-Awareness: <b>pr_numa</b> and <b>bfs_numa</b>. The expected data layout is an adjacency list. 

Most files contain the currently pushed data layouts for the algorithm except BFS and PR over a grid which are stored in separate files (bfsgrid, prgrid).



