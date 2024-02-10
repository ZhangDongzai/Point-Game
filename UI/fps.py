# 游戏界面

from setting import *

import pygame


class FPS(pygame.sprite.Sprite):
    size = int(40 * RATIO)
    pos = 10 * WIDTH_RATIO, 690 * HEIGHT_RATIO
    color = YELLOW
    def __init__(self, *groups, game: object) -> None:
        """
        初始化FPS显示组件.

        :param game: 游戏类对象.
        :param groups: 可选的组参数.
        """
        super().__init__(*groups)

        self.game = game
        self.font = pygame.font.Font(name=None, size=self.size)
        self.fps = 0

        # 初始化图像
        self.image = self.font.render(f"FPS: {self.fps}", False, self.color)

        # 初始化位置
        self.rect = self.image.get_rect()
        self.rect.topleft = self.pos

    def update(self, *args, **kwargs) -> None:
        """
        更新函数, 用于更新FPS显示的位置和内容.
        """
        # 重置图像
        self.fps = int(self.game.clock.get_fps())                               # 获取当前帧率
        self.image = self.font.render(f"FPS: {self.fps}", False, self.color)    # 使用字体渲染FPS显示内容

        # 重置位置
        self.rect = self.image.get_rect()             # 获取图像的矩形区域
        self.rect.x, self.rect.y = self.pos           # 设置FPS显示的位置
