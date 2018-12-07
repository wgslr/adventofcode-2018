#!/usr/bin/env python3

import networkx as nx

INPUT = "./input.csv"


if __name__ == "__main__":
    print("Reading")

    # print(open(INPUT).read())
    graph = nx.read_edgelist(INPUT, create_using=nx.DiGraph, nodetype=str)

    # print(graph.edges.items())

    s = nx.algorithms.dag.lexicographical_topological_sort(graph)
    print(''.join(s))
