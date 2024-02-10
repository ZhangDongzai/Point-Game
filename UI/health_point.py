# 血量界面文件

from setting import *
import UI

import pygame


class HealthPoint(pygame.sprite.Sprite):
    # 角色属性
    color = RED
    size = width, height = 400 * WIDTH_RATIO, 40 * HEIGHT_RATIO
    
    def __init__(self, *groups, sprite: pygame.sprite.Sprite, setting: dict) -> None:
        super().__init__(*groups)

        self.sprite = sprite
        self.number = 100
        self.setting = setting

        self.draw() # 初始化图像

        self.rect = self.image.get_rect() # 初始化位置

    def draw(self) -> None:
        """绘制血量"""
        width = self.width * (self.number / 100) # 计算长度
        self.size = width, self.height # 重新赋值
        self.image = pygame.Surface(self.size) # 重置图像
        self.image.fill(RED) # 填充颜色
        self.rect = self.image.get_rect() # 重置位置

        if self.setting["NUMBER"] == 1: # 玩家1
            self.rect.topright = SCREEN_WIDTH * 0.5 - 1, 0
        elif self.setting["NUMBER"] == 2: # 玩家2
            self.rect.topleft = SCREEN_WIDTH * 0.5 + 1, 0

    def update(self, *args, **kwargs) -> None:
        # 绘制血量
        self.draw()

    def checkHealth(self) -> None:
        """检查血量"""
        if self.number <= 0:
            self.sprite.kill()
            self.kill()

            # 判断获胜
            if len(self.sprite.game.sprite.sprites()) == 1:
                self.sprite.game.state = 1
                self.sprite.game.checkState()

    def hurt(self) -> None:
        """受伤"""
        self.number -= 10
        self.checkHealth()
