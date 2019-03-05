import sys, fileinput
from graph import Graph

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

if __name__ == "__main__":
    anthill = Graph()
    start = end = ""
    text = [line.strip() for line in fileinput.input() if validLine(line)]
    nb_ants = text.pop(0)

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

    """ add links """
    for (i, elem) in enumerate(text):
        if not validLink(elem):
            continue
        anthill.add_edge(tuple(elem.split('-')))

    print(anthill.__str__())
