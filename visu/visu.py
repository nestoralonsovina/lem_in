from operator import itemgetter
import time
import pygame

class Visualizer:
    def __init__(self, graph, start, end):
        self.start = start
        self.end = end
        self.__graph = graph
        self.win_size = (1600, 900)
        self.__get_max()
        self.colors = {
                'background': pygame.Color(58, 64, 90),
                'white': pygame.Color(255, 255, 255),
                'green': pygame.Color(0, 255, 0),
                'red': pygame.Color(255, 0, 0),
                'default': pygame.Color(0, 0, 255)
                }

    def __get_max(self):
        self.coord_lst = self.__graph.coord()
        self.max_x = max(self.coord_lst, key=itemgetter(0))[0]
        self.max_y = max(self.coord_lst, key=itemgetter(1))[1]

    def __maxcoord__(self):
        print("max_x: %d, max_y: %d" % (self.max_x, self.max_y))

    def __calc_ratio(self):
        self.transformation_ratio = list(self.win_size)
        if self.max_x != 0:
            self.transformation_ratio[0] /= self.max_x + 3
        if self.max_y != 0:
            self.transformation_ratio[1] /= self.max_y + 3

    def __apply_ratio(self):
        for coord in self.coord_lst:
            coord[0] = int((coord[0] + 1) * self.transformation_ratio[0])
            coord[1] = int((coord[1] + 1) * self.transformation_ratio[1])
            if self.max_y == 0:
                coord[1] = self.win_size[1] // 2

    def __draw_nodes(self):
        verts = self.__graph.vertices()
        for (i, node_coord) in enumerate(self.coord_lst):
            color = self.colors['default']
            if verts.index(self.start) == i:
                color = self.colors['green'] 
            elif verts.index(self.end) == i:
                color = self.colors['red']
            pygame.draw.circle(self.win, color, node_coord, 15)

    def __draw_lines(self):
        verts = self.__graph.vertices()
        edges = self.__graph.edges()
        for (i, vertex) in enumerate(verts):
            print(vertex, edges[i])
            for edge in edges[i]:
                pygame.draw.line(self.win, self.colors['white'],
                        self.coord_lst[verts.index(vertex)],
                        self.coord_lst[verts.index(edge)])

    def init(self):
        pygame.init()

        self.win = pygame.display.set_mode(self.win_size)
        pygame.display.set_caption("Lem-in visualizer")

        self.win.fill(self.colors['background'])
        self.__calc_ratio()
        self.__apply_ratio()
        self.__draw_lines()
        self.__draw_nodes()
        pygame.display.update()
        run = True
        while run:
            pygame.time.delay(100)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    run = False
            keys = pygame.key.get_pressed()
        pygame.quit()
