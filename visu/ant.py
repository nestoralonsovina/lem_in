from math import sqrt

class Ant:
    def __init__(self, start_room, x, y, vel = 5):
        self.room = start_room
        self.x = x
        self.y = y
        self.vel = vel

    def move(self, nx, ny, new_room):
        self.room = new_room;
        dist = sqrt((nx - self.x)**2 + (ny - self.y)**2)
