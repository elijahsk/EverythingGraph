#!/usr/bin/python2.7

import sys, random, math;
from operator import itemgetter

### Generates a random directed graph with edge labels using preferential attachment
### The labels can follow either a uniform or normal distribution

def exitMain():
    sys.exit(1);

if(len(sys.argv) <= 4):
    print("usage python2.7 " + sys.argv[0] + " unlabeled_file_path no_of_labels P_1st_label[0-1] P_2nd_label[0-1] ...");
    exitMain();

try:
    filePath = sys.argv[1];
    noOfLabels = int(sys.argv[2]);
    p = [0];
    p.append(sys.argv[3]);
    for i in range(4, len(sys.argv)):
        p.append(sys.argv[i] + p[-1]);
    print(p)；
    name = filePath[:-4] + "_2_" + str(p)
except:
    print("Invalid argument(s)")
    exitMain();


infile = open(filePath, 'r');
f = open(name, 'w');


random.seed();

dgraph = [];
line = infile.readline();
while line:
    nodes = line.split('\t');
    node1 = nodes[0];
    node2 = nodes[1][:-1]; 

    randValue = random.random();

    label = -1;

    for i in range(len(p) - 1):
        if (p[i] <= randValue < p[i + 1]):
            label = i; 
            break;
            
    if label == -1:    
        label = random.uniform(len(p), noOfLabels);

    dgraph.append((node1, node2, label));

    line = infile.readline();
infile.close();

dgraph = sorted(dgraph,key=lambda x: x[0], reverse=False);

for triple in dgraph:
    (s,t,l) = triple;
    base = 0;
    ss = str(s) + " " + str(t) + " " + str(l);
    f.write(ss + "\n");

f.close();
