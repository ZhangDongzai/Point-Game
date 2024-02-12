# 血量界面文件

from setting import *
import UI

import pygame


class HealthPoint(pygame.sprite.Sprite):
    # 角色属性
    color = RED
    size = width, height = 400 * WIDTH_RATIO, 40 * HEIGHT_RATIO
    font_color = WHITE
    font_size = int(50 * RATIO)
    
    def __init__(self, *groups, sprite: pygame.sprite.Sprite, setting: dict) -> None:
        super().__init__(*groups)

        self.sprite = sprite
        self.max_number = 100
        self.__number = self.max_number
        self.setting = setting
        self.font = pygame.font.Font(None, size=self.font_size)

        self.draw() # 初始化图像

        self.rect = self.image.get_rect() # 初始化位置

    def draw(self) -> None:
        """绘制血量"""
        # 计算长度
        width = self.width * (self.number / 100)
        self.size = width, self.height

        # 绘制图像
        self.image = pygame.Surface(self.size)
        self.image.fill(RED)

        # 设置位置
        self.rect = self.image.get_rect() 

        if self.setting["NUMBER"] == 1: # 玩家1
            self.rect.topright = SCREEN_WIDTH * 0.5 - 1, 0
        elif self.setting["NUMBER"] == 2: # 玩家2
            self.rect.topleft = SCREEN_WIDTH * 0.5 + 1, 0

        # 绘制数值
        text = f"{self.__number}"
        font_image = self.font.render(text, False, self.font_color)

        # 设置位置
        font_rect = font_image.get_rect()
        if self.setting["NUMBER"] == 1: # 玩家1
            font_rect.midright = self.width - 1, self.height / 2
        elif self.setting["NUMBER"] == 2: # 玩家2
            font_rect.midleft = 1, self.height / 2

        # 绘制至图像上
        self.image.blit(font_image, font_rect)

    def update(self, *args, **kwargs) -> None:
        # 绘制血量
        self.draw()

    @property
    def number(self) -> int:
        return self.__number

    @number.setter
    def number(self, number: int) -> None:
        """受伤"""
        self.__number = number

        if self.number <= 0:
            self.sprite.kill()
            self.kill()

            if len(self.sprite.game.sprite.sprites()) == 1:
                self.sprite.game.state = 2
