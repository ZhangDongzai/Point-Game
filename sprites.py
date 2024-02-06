# 角色文件

from setting import *

import pygame
import math



class Point(pygame.sprite.Sprite):
    # 角色属性
    color = WHITE                                       # 图像颜色
    movement_speed = 200                                # 移动速度(单位: 像素/S)
    rotation_speed = 3                                  # 旋转速度(单位: 弧度/S)
    side = 30                                           # 图像边长
    screen_center = x, y = SCREEN_CENTER                # 图像中心(绝对位置)
    angle = 0                                           # 默认方向(单位: 弧度)(O朝右)

    def __init__(self, game: object, *groups) -> None:
        super().__init__(*groups)

        # 初始化属性
        self.game = game                                # 游戏类
        self.size = self.side, self,side                # 图像尺寸
        self.radius = self.side / 2                     # 圆的半径
        self.image_center = self.radius, self.radius    # 图像中心(相对位置)
        
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
        self.rect.x, self.rect.y = self.x - self.radius, self.y - self.radius

    def update(self, *args, **kwargs) -> None:
        # 计算当前帧速度
        movement_speed = self.movement_speed * self.game.delta_time
        rotation_speed = self.rotation_speed * self.game.delta_time
        movement_speed_sin = movement_speed * math.sin(self.angle)
        movement_speed_cos = movement_speed * math.cos(self.angle)

        # 监控键盘
        key_pressed = pygame.key.get_pressed()

        # 平移
        x, y = 0, 0
        if key_pressed[pygame.K_w]:             # 前进
            x += movement_speed_cos
            y += movement_speed_sin
        if key_pressed[pygame.K_s]:             # 后退
            x -= movement_speed_cos
            y -= movement_speed_sin
        if key_pressed[pygame.K_a]:             # 左移
            x += movement_speed_sin
            y -= movement_speed_cos
        if key_pressed[pygame.K_d]:             # 右移
            x -= movement_speed_sin
            y += movement_speed_cos
        
        if (x != 0) and (y != 0):               # 按两个键时 x, y 乘 sin(45) 或 cos(45)
            x *= 0.7071
            y *= 0.7071
        
        self.rect.x = self.x - self.radius
        self.rect.y = self.y - self.radius

        # 旋转
        if key_pressed[pygame.K_LEFT]:
            self.angle -= rotation_speed
        if key_pressed[pygame.K_RIGHT]:
            self.angle += rotation_speed
        self.angle %= math.tau

        # 绘制图像
        pygame.draw.line(surface=self.game.screen,
                         color=self.color,
                         start_pos=(self.x, self.y),
                         end_pos=(self.x + SCREEN_WIDTH * math.cos(self.angle),
                                  self.y + SCREEN_WIDTH * math.sin(self.angle)))
        
