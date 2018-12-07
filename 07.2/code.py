#!/usr/bin/env python3

import networkx as nx

INPUT = "./input.nx"
WORKERS = 5

def time(step):
    return 60 + ord(step) - ord('A') + 1


def cando(name, graph, compl):
    return all((n in compl for n in graph.predecessors(name)))


def future(end_at, t):
    return {x: end_at[x] for x in end_at if x > t}


if __name__ == "__main__":
    graph = nx.read_edgelist(INPUT, create_using=nx.DiGraph, nodetype=str)
    todo_all = list(nx.algorithms.dag.lexicographical_topological_sort(graph))

    compl = set()
    end_at = dict()
    todo = set()
    free = WORKERS

    while free > 0 and any(cando(x, graph, compl) for x in todo_all):
        for task in todo_all:
            if(cando(task, graph, compl)):
                free -= 1
                end = time(task)
                end_at[end] = end_at.get(end, []) + [task]
                todo_all.remove(task)
                break

    t = 0
    while True:
        ends = end_at.get(t, [])
        compl.update(set(ends))
        for task in ends:
            free += 1
            todo.update(graph.neighbors(task))
            todo -= compl

        found = True
        while free > 0 and found:
            found = False
            for task in todo:
                if free == 0:
                    break
                if cando(task, graph, compl) :
                    free -= 1
                    end = time(task) + t
                    end_at[end] = end_at.get(end, []) + [task]
                    todo.remove(task)
                    found = True
                    break

        if len(compl) == len(graph.nodes()):
            break

        end_at = future(end_at, t)
        t = min(end_at)

    print(t)
