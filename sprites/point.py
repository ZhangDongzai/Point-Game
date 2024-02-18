# Point角色文件

from setting import *
import sprites
import UI

import pygame
import math
import time


class Point(pygame.sprite.Sprite):
    # 角色属性
    color = WHITE                                       # 图像颜色
    movement_speed = 200 * RATIO                        # 移动速度(单位: 像素/S)
    rotation_speed = 3                                  # 旋转速度(单位: 弧度/S)
    side = 30 * RATIO                                   # 图像边长

    def __init__(self, *groups, game: object, setting: dict) -> None:
        super().__init__(*groups)

        # 初始化属性
        self.game = game                                # 游戏类
        self.setting = setting                          # 角色键位
        self.size = self.side, self.side                # 图像尺寸
        self.radius = self.side / 2                     # 圆的半径
        self.image_center = self.radius, self.radius    # 图像中心(相对位置)
        self.x, self.y = setting["POS"]["POINT"]
        self.angle = setting["ANGLE"]["POINT"]          # 默认方向(单位: 弧度)(O朝右)
        self.bullets = pygame.sprite.Group()
        self.bullet_number = 0
        self.hurt_number = 0
        self.ui_bullet = UI.bullet.Bullet(self.game.game_ui, setting=self.setting)
        self.ui_health_point = UI.health_point.HealthPoint(self.game.game_ui, sprite=self, setting=setting)
        
        # 加载图像
        self.image = pygame.Surface(size=self.size)
        self.image.set_colorkey(BLACK)                  # 设置黑色为透明色
        self.image.fill(BLACK)
        pygame.draw.circle(surface=self.image,
                           color=self.color,
                           center=self.image_center,
                           radius=self.radius)
        
        # 设置位置
        self.rect = self.image.get_rect()
        self.rect.center = self.x, self.y

    def update(self, *args, **kwargs) -> None:
        # 监控键盘
        key_pressed = pygame.key.get_pressed()

        # 移动
        self.movement(key_pressed)

        # 子弹
        self.ui_bullet.is_reload_bullet(key_pressed)
        if self.ui_bullet.is_launch_bullet(key_pressed):
            self.bullet_number += 1
            sprites.bullet.Bullet(self.bullets, game=self.game, sprite=self)

    def movement(self, key_pressed: pygame.key.ScancodeWrapper) -> None:
        # 计算当前帧速度
        movement_speed = self.movement_speed * self.game.delta_time
        rotation_speed = self.rotation_speed * self.game.delta_time
        movement_speed_sin = movement_speed * math.sin(self.angle)
        movement_speed_cos = movement_speed * math.cos(self.angle)

        # 平移
        x, y = 0, 0
        if key_pressed[self.setting["KEY"]["UP"]]:         # 前进
            x += movement_speed_cos
            y += movement_speed_sin
        if key_pressed[self.setting["KEY"]["DOWN"]]:       # 后退
            x -= movement_speed_cos
            y -= movement_speed_sin

        # 撞墙
        if not self.game.map.is_hit(pos=(self.x + x, self.y)):
            self.x += x
        if not self.game.map.is_hit(pos=(self.x, self.y + y)):
            self.y += y
        
        self.rect.center = self.x, self.y

        # 旋转
        if key_pressed[self.setting["KEY"]["LEFT"]]:
            self.angle -= rotation_speed
        if key_pressed[self.setting["KEY"]["RIGHT"]]:
            self.angle += rotation_speed
        self.angle %= math.tau

    def draw(self) -> None:
        # 绘制方向指示
        up_point = (self.x + math.cos(self.angle) * 40 * RATIO,
                    self.y + math.sin(self.angle) * 40 * RATIO)
        down_point = (self.x + math.cos(self.angle) * 30 * RATIO,
                      self.y + math.sin(self.angle) * 30 * RATIO)
        left_point = (self.x + math.cos(self.angle - 0.5) * 30 * RATIO,
                      self.y + math.sin(self.angle - 0.5) * 30 * RATIO)
        right_point = (self.x + math.cos(self.angle + 0.5) * 30 * RATIO,
                       self.y + math.sin(self.angle + 0.5) * 30 * RATIO)
        points = (up_point, left_point, down_point, right_point)

        pygame.draw.polygon(surface=self.game.screen, color=WHITE, points=points)

        # 绘制子弹
        if len(self.bullets.sprites()) != 0:
            for bullet in self.bullets.sprites():
                bullet.update()
                self.game.screen.blit(bullet.image, bullet.rect)

    def kill(self) -> None:
        self.bullets.empty()
        super().kill()
