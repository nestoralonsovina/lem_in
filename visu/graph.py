class Graph:
    def __init__(self, graph_dict = None):
        if not graph_dict:
            graph_dict = {}
            graph_coord = {}
        self.__graph_dict = graph_dict
        self.__graph_coord = graph_coord

    def vertices(self):
        """ returns the vertices of the graph_dict """
        return list(self.__graph_dict.keys())

    def coord(self):
        return list(self.__graph_coord.values())

    def edges(self):
        """ returns the edges of a graph """
        return self.__generate_edges()

    def add_vertex(self, vertex, x, y):
        """ If the vertex is not in self.__graph_dict, a key
        with an empty list as a value is added to the dictionary.
        Otherwise nothing has to be done.
        """
        if vertex not in self.__graph_dict:
            self.__graph_dict[vertex] = []
            if [int(x), int(y)] not in self.__graph_coord.values():
                self.__graph_coord[vertex] = [int(x), int(y)]

    def add_edge(self, edge):
        """ asumes that edge is of type set, tuple or list;
        between two vertices can be multiple edges!
        """
        edge = set(edge)
        vertex1 = edge.pop()
        if edge:
            vertex2 = edge.pop()
        else:
            vertex2 = vertex1
        if vertex1 in self.__graph_dict:
            self.__graph_dict[vertex1].append(vertex2)
            self.__graph_dict[vertex2].append(vertex1)
        else:
            self.__graph_dict[vertex1] = [vertex2]
            self.__graph_dict[vertex2] = [vertex1]

    def __generate_edges(self):
        edges = []
        for vertex in self.__graph_dict:
            edges.append(list(set(self.__graph_dict[vertex])))
        return edges

    def __str__(self):
        res = "vertices: "
        for k in self.__graph_dict:
            res += str(k) + " "
        res += "\ncoord: "
        for coor in self.__graph_coord.values():
            res += str(coor) + " "
        res += "\nedges: "
        for edge in self.__generate_edges():
            res += str(edge) + " "
        return res


