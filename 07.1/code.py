#!/usr/bin/env python3

import networkx as nx

INPUT = "./input.nx"


if __name__ == "__main__":
    graph = nx.read_edgelist(INPUT, create_using=nx.DiGraph, nodetype=str)
    s = nx.algorithms.dag.lexicographical_topological_sort(graph)

    print(''.join(s))
