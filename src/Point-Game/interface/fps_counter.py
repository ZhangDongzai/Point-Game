import pygame

from config import *


class FPS_Counter(pygame.sprite.Sprite):
    """Show fps on the screen."""

    size = DATA["fps_counter"]["size"]
    color = DATA["fps_counter"]["color"]

    def __init__(self, *groups) -> None:
        super().__init__(*groups)

        self.rect = pygame.Rect(10, 10, 0, 0)
        self.font = pygame.Font(None, self.size)

    def update(self, fps: float) -> None:
        self.image = self.font.render(text=f"FPS: {round(fps, 2)}",
                                      antialias=DATA["window"]["antialias"],
                                      color=self.color)
