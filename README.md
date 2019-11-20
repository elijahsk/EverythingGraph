# Multicore In-Memory BFS on Labeled Graphs


README

This repository contains code for CS6284 Final Project on Multicore In-Memory BFS on Labeled Graphs

<h1>Requirement</h1>

The code needs to be compiled and run on Linux platform with gcc version of 5.0 and above.

The gcc compiler needs to support Cilk Plus. As gcc have full support for Cilk Plus since version 5.0, this should not be an issue.

<h1>Compilation</h1>

To compile the code, enter the repository and run command <code> make </code>. 

<h1>Input Generation</h1>

The input file is a graph dataset encoded as a binary file. 

The input file can be generated in the following steps:

1. Enter repository

2. Enter command <code> dataGen/PaRMAT/Release/PaRMAT -nVertices [no. of vertices] -nEdges [no. of edges]</code>, where [no. of vertices] and [no. of edges] are integer values to be filled in. This command generates a text file named <strong>out.txt</strong> with the specified number of vertices and number of labels.

3. Enter command <code>python dataGen/addnLabelsByProbability.py out.txt [no. of labels] [p1] [p2] ...</code>, where [no. of labels] is an integer value indicating the number of labels to be put in the graph, and [p1], [p2], ..., [pn], are float values indicating the probability of having the 1st, 2nd, ..., nth label. This command generates a text file named <strong>out</strong> with edge data from <strong>out.txt</strong> and additional labeled data.

4. Enter command <code>dataGen/writeBinary out</code>. This command generates a binary file named <strong>out.bin</strong> in the current directory based on the out file.

<h1>Running the code</h1>

To run the code you need to call the corresponding algorithm binary with a number of required options:

<code>./algorithm_binary –n [no. of vertices] –f [path to binary graph data] -l [labelSet] [other optional commands]</code>

[labelSet] is an integer value between 1 and 255. This value is interpreted as a binary value e.g. entering value 7 gives a labelSet of 00000111, indicating that the labelSet contains the 1st, 2nd and 3rd label.

Help message on other optional command will be displayed when the algorithm_binary is not run with the essential commands.

The available algorithm_binary are <strong>bfs_simple</strong>, <strong>bfsgrid_cilk</strong>, and <strong>bfs_numa</strong>.
