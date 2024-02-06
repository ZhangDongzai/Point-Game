# 游戏界面

from setting import *

import pygame


class FPS(pygame.sprite.Sprite):
    def __init__(self, game: object, *groups) -> None:
        super().__init__(*groups)

        self.game = game
        self.font = pygame.font.Font(None, size=FPS_SIZE)
        self.fps = 0

        # 初始化图像
        self.image = self.font.render(f"FPS: {self.fps}", False, FPS_COLOR)

        # 初始化位置
        self.rect = self.image.get_rect()
        self.rect.x, self.rect.y = FPS_POS

    def update(self, *args, **kwargs) -> None:
        # 重置图像
        self.fps = int(self.game.clock.get_fps())
        self.image = self.font.render(f"FPS: {self.fps}", False, FPS_COLOR)

        # 重置位置
        self.rect = self.image.get_rect()
        self.rect.x, self.rect.y = FPS_POS
