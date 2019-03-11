import pygame, os


def redraw_gamewindow():
    pygame.display.update()


def main():

    run = True
    while runL

        for event in pygame.evet.get():
            if event.type == pygame.QUIT:
                pygame.quit()
