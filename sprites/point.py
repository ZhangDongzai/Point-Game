# Point角色文件

from setting import *
import sprites.bullet

import pygame
import math
import time


class Point(pygame.sprite.Sprite):
    # 角色属性
    color = WHITE                                       # 图像颜色
    movement_speed = 200                                # 移动速度(单位: 像素/S)
    rotation_speed = 3                                  # 旋转速度(单位: 弧度/S)
    side = 30                                           # 图像边长
    x, y = SCREEN_CENTER                                # 图像中心(绝对位置)
    angle = 0                                           # 默认方向(单位: 弧度)(O朝右)

    def __init__(self, game: object, *groups) -> None:
        super().__init__(*groups)

        # 初始化属性
        self.game = game                                # 游戏类
        self.size = self.side, self.side                # 图像尺寸
        self.radius = self.side / 2                     # 圆的半径
        self.image_center = self.radius, self.radius    # 图像中心(相对位置)
        self.bullets = pygame.sprite.Group()
        self.bullet_time = 0
        
        # 加载图像
        self.image = pygame.Surface(size=self.size)
        pygame.draw.circle(surface=self.image,
                           color=self.color,
                           center=self.image_center,
                           radius=self.radius)
        
        # 设置位置
        #   注意:
        #   因为Rect实际在Surface的左上角,
        #   所以计算Surface的中心要在Rect.x, Rect.y的基础上分别减一半的边长.
        self.rect = self.image.get_rect()
        self.rect.center = self.x, self.y

    def update(self, *args, **kwargs) -> None:
        # 监控键盘
        key_pressed = pygame.key.get_pressed()

        # 移动
        self.movement(key_pressed)

        # 子弹
        if key_pressed[pygame.K_j] and (time.time() - self.bullet_time > 0.1):
            self.bullet_time = time.time()
            sprites.bullet.Bullet(self.bullets, game=self.game, sprite=self)

    def movement(self, key_pressed: pygame.key.ScancodeWrapper) -> None:
        # 计算当前帧速度
        movement_speed = self.movement_speed * self.game.delta_time
        rotation_speed = self.rotation_speed * self.game.delta_time
        movement_speed_sin = movement_speed * math.sin(self.angle)
        movement_speed_cos = movement_speed * math.cos(self.angle)

        # 平移
        if key_pressed[pygame.K_w]:             # 前进
            self.x += movement_speed_cos
            self.y += movement_speed_sin
        if key_pressed[pygame.K_s]:             # 后退
            self.x -= movement_speed_cos
            self.y -= movement_speed_sin

        if self.x < 0:
            self.x = 0
        if self.x > SCREEN_WIDTH:
            self.x = SCREEN_WIDTH
        if self.y < 0:
            self.y = 0
        if self.y > SCREEN_HEIGHT:
            self.y = SCREEN_HEIGHT
        
        self.rect.center = self.x, self.y

        # 旋转
        if key_pressed[pygame.K_a]:
            self.angle -= rotation_speed
        if key_pressed[pygame.K_d]:
            self.angle += rotation_speed
        self.angle %= math.tau

    def draw(self) -> None:
        # 绘制方向指示
        up_point = (self.x + math.cos(self.angle) * 40,
                    self.y + math.sin(self.angle) * 40)
        down_point = (self.x + math.cos(self.angle) * 30,
                      self.y + math.sin(self.angle) * 30)
        left_point = (self.x + math.cos(self.angle - 0.5) * 30,
                      self.y + math.sin(self.angle - 0.5) * 30)
        right_point = (self.x + math.cos(self.angle + 0.5) * 30,
                       self.y + math.sin(self.angle + 0.5) * 30)
        points = (up_point, left_point, down_point, right_point)

        pygame.draw.polygon(surface=self.game.screen, color=WHITE, points=points)

        # 绘制子弹
        if len(self.bullets.sprites()) != 0:
            for bullet in self.bullets.sprites():
                bullet.update()
                self.game.screen.blit(bullet.image, bullet.rect)
