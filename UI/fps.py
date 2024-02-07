# 游戏界面

from setting import *

import pygame


class FPS(pygame.sprite.Sprite):
    def __init__(self, game: object, *groups) -> None:
        """
        初始化FPS显示组件.

        :param game: 游戏类对象.
        :param groups: 可选的组参数.
        """
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
        """
        更新函数, 用于更新FPS显示的位置和内容.
        """
        # 重置图像
        self.fps = int(self.game.clock.get_fps())                               # 获取当前帧率
        self.image = self.font.render(f"FPS: {self.fps}", False, FPS_COLOR)     # 使用字体渲染FPS显示内容

        # 重置位置
        self.rect = self.image.get_rect()             # 获取图像的矩形区域
        self.rect.x, self.rect.y = FPS_POS            # 设置FPS显示的位置
