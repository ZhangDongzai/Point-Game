# Bullet角色文件

from setting import *

import pygame
import math
import random


class Bullet(pygame.sprite.Sprite):
    # 角色属性
    color = WHITE
    speed = 1000 * RATIO
    side = 10 * RATIO
    hurt = 10
    good_hurt = 0.1

    def __init__(self, *groups, game: object, sprite: pygame.sprite.Sprite) -> None:
        super().__init__(*groups)

        self.game = game
        self.sprite = sprite
        self.angle = sprite.angle
        self.size = self.side, self.side
        self.radius = self.side / 2
        self.center = self.radius, self.radius
        self.good_hurt_list = [True for _ in range(int(self.good_hurt * 100))] + \
                              [False for _ in range(int((1 - self.good_hurt) * 100))]

        # 初始化图像
        self.image = pygame.Surface(size=self.size)
        self.image.set_colorkey(BLACK)                  # 设置黑色为透明色
        self.image.fill(BLACK)
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

        # 判定是否撞墙
        if self.game.map.is_hit((self.x, self.y)):
            self.kill()

        # 判断是否撞角色
        for sprite in self.game.sprite.sprites():
            if sprite is self.sprite:
                continue
            elif sprite.rect.colliderect(self.rect):
                self.kill()
                self.sprite.bullet_number += 1

                hurt = self.hurt
                if random.choice(self.good_hurt_list):
                    hurt += 5
                sprite.ui_health_point.number -= hurt
                break
