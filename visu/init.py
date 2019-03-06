import sys, fileinput
from graph import Graph
from visu import Visualizer

def validLine(line):
    if line.startswith("##") or not line.startswith("#"):
        return True
    return False

def validRoom(line):
    if not line.startswith("L") and len(line.split(' ')) == 3:
        return True
    return False

def validLink(line):
    if not line.startswith("L") and len(line.split('-')) == 2:
        return True
    return False

def get_graph_info(text, Graph):
    nb_ants = text.pop(0)
    last_i = 0

    """ add vertex """
    for (i, elem) in enumerate(text):
        if validLink(elem):
            break
        if elem == "##start":
            start = text[i + 1].split()[0]
        elif elem == "##end":
            end = text[i + 1].split()[0]
        else:
            anthill.add_vertex(*elem.split(' '))
        last_i = i

    """ update text to what there is after the rooms"""
    text = text[last_i:]

    """ add links """
    for (i, elem) in enumerate(text):
        if not validLink(elem):
            continue
        anthill.add_edge(tuple(elem.split('-')))
        last_i = i

    return last_i, start, end


if __name__ == "__main__":
    anthill = Graph()
    text = [line.strip() for line in fileinput.input() if validLine(line)]
    last_i, start, end = get_graph_info(text, Graph);

    """ update text to what there is after the map information """
    text = text[last_i + 1:]

    """ print general graph information """
    print("start: %s, end: %s" %(start, end))
    # print(anthill.edges())

    """ start visualizer """
    visu = Visualizer(anthill, start, end)
    visu.init()
