# 胜利界面

from setting import *

import pygame


class Win(pygame.sprite.Sprite):
    color = WHITE
    size = int(500 * RATIO)

    def __init__(self, *groups) -> None:
        super().__init__(*groups)

        self.font = pygame.font.Font(None, size=self.size)
        self.image = self.font.render("WIN", False, self.color)
        self.rect = self.image.get_rect()
        self.rect.center = SCREEN_CENTER
