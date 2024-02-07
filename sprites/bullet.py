# Bullet角色文件

from setting import *

import pygame
import math


class Bullet(pygame.sprite.Sprite):
    # 角色属性
    color = WHITE
    speed = 200
    side = 10

    def __init__(self, *groups, game: object, sprite: pygame.sprite.Sprite) -> None:
        super().__init__(*groups)

        self.game = game
        self.sprite = sprite
        self.angle = sprite.angle
        self.size = self.side, self.side
        self.radius = self.side / 2
        self.center = self.radius, self.radius

        # 初始化图像
        self.image = pygame.Surface(size=self.size)
        pygame.draw.circle(surface=self.image,
                           color=self.color,
                           center=self.center,
                           radius=self.radius)

        # 初始化位置
        self.rect = self.image.get_rect()
        self.rect.center = self.x, self.y = sprite.rect.center

    def update(self, *args, **kwargs) -> None:
        # 计算速度
        speed = self.speed * self.game.delta_time
        speed_sin = speed * math.sin(self.angle)
        speed_cos = speed * math.cos(self.angle)

        # 移动
        self.x += speed_cos
        self.y += speed_sin
        self.rect.center = self.x, self.y

        if (self.x < 0) or (self.x > SCREEN_WIDTH) or (self.y < 0) or (self.y > SCREEN_HEIGHT):
            self.kill()
