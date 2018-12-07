#!/usr/bin/env python3

import networkx as nx

INPUT = "./input.nx"


def time(step):
    return 60 + ord(step) - ord('A') + 1


def cando(name, graph, compl):
    # print(name, node)
    # print(graph)
    # print(graph.predecessors(node))
    # print([(n in compl) for n in graph.predecessors(name)])
    return all((n in compl for n in graph.predecessors(name)))

def future(end_at, t):
    return {x: end_at[x] for x in end_at if x > t}

if __name__ == "__main__":
    print("Reading")

    # print(open(INPUT).read())
    graph = nx.read_edgelist(INPUT, create_using=nx.DiGraph, nodetype=str)

    # print(graph.edges.items())

    s = nx.algorithms.dag.lexicographical_topological_sort(graph)
    print(''.join(s))

    compl = set()
    t = 0
    WORKERS = 5
    free_on = [0 for _ in range(WORKERS)]
    end_on = dict()
    s = nx.algorithms.dag.lexicographical_topological_sort(graph)
    todo_all = list(s)
    todo = set()

    print(time('A'))

    print("todo: ", todo)

    print(cando('B', graph, compl))
    print(cando('C', graph, compl))

    free = WORKERS

    while free > 0 and any(cando(x, graph, compl) for x in todo_all):
        for task in todo_all:
            if(cando(task, graph, compl)):
                free -= 1
                end = time(task)
                end_on[end] = end_on.get(end, []) + [task]
                todo_all.remove(task)
                break

    print(end_on)

    while len(compl) != len(graph.nodes()):
        print("t = {}".format(t))
        print("{} {}".format(len(compl), len(graph.nodes())))
        ends = end_on.get(t, [])
        compl.update(set(ends))
        print("compl: ", compl)
        for task in ends:
            free += 1
            todo.update(graph.neighbors(task))
            todo -= compl
            print("{} neighs: {}".format( task, list(graph.neighbors(task))))
            print("newtodo: ", todo)


            # for succ in graph.neighbors(task):
            #     if succ not in todo_all:
            #         continue
            #     print([x in compl for x in graph.predecessors(succ)])
            #     if all((x in compl for x in graph.predecessors(succ))) :
            #         print("add {} as doable".format(succ))
            #         todo += [succ]
            #         todo_all.remove(succ)
            #     else:
            #         print("{} not doable because {}".format(succ, [x for x in graph.predecessors(succ) if x not in compl]))

        # print("free: ",free)
        print(todo)
        found = True
        while free > 0 and found:
            found = False
            for task in todo:
                print("task = ", task)
                if free == 0:
                    break
                if cando(task, graph, compl) :
                    free -= 1
                    end = time(task) + t
                    print('add end_on {} {}, free: {} '.format(end, task, free))
                    end_on[end] = end_on.get(end, []) + [task]
                    todo.remove(task)
                    print(todo)
                    found = True
                    break

        # print(end_on)
        if len(compl) == len(graph.nodes()):
            break
        end_on = future(end_on, t)
        print("future: ", end_on, "TODO: ", todo)
        t = min(end_on)

    print(t)
