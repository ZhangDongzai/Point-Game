# 地图一文件

from setting import *

import pygame


class Map:
    map = [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
          ]
    background_color = BLACK
    rect_color = WHITE

    def __init__(self, game: object):
        self.game = game
    
        # 根据窗口大小计算每个格子的宽和高
        self.width = SCREEN_WIDTH / len(self.map[0])
        self.height = SCREEN_HEIGHT / len(self.map)

        # 初始化图像
        self.image = pygame.Surface(SCREEN_SIZE)
        self.draw()

        # 初始化位置
        self.rect = self.image.get_rect()
        self.rect.x, self.rect.y = 0, 0

    def update(self, *args, **kwargs) -> None:
        self.draw()
    
    def draw(self) -> None:
        """使用`pygame.draw.rect`根据`self.map`的内容绘制地图."""
        self.image.fill(self.background_color)
        for y, row in enumerate(self.map):
            for x, colnum in enumerate(row):
                if colnum:
                    rect = pygame.Rect(x * self.width,
                                       y * self.height,
                                       self.width,
                                       self.height)
                    pygame.draw.rect(surface=self.image,
                                     color=self.rect_color,
                                     rect=rect,
                                     width=1)
        