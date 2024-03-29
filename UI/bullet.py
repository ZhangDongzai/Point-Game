# 子弹界面文件

from setting import *

import pygame
import time


class Bullet(pygame.sprite.Sprite):
    size = int(50 * RATIO)
    color = YELLOW
    max_number = 50

    def __init__(self, *groups, setting: dict[str, dict[str, int]]) -> None:
        super().__init__(*groups)

        self.font = pygame.font.Font(None, size=self.size)
        self.number = self.max_number
        self.bullet_time = 0
        self.setting = setting
        self.pos = setting["POS"]["BULLET"]
        self.image = None
        self.rect = None

        self.update()

    def update(self, *args, **kwargs) -> None:
        # 加载图像
        self.image = self.font.render(f"{self.number}/{self.max_number}", False, self.color)

        # 设置位置
        self.rect = self.image.get_rect()
        self.rect.topleft = self.pos

    def is_reload_bullet(self, key_pressed: pygame.key.ScancodeWrapper) -> None:
        """检测是否换弹"""
        if key_pressed[self.setting["KEY"]["RELOAD_BULLET"]]:
            self.number = self.max_number

    def is_launch_bullet(self, key_pressed: pygame.key.ScancodeWrapper) -> bool:
        """检测是否发射子弹"""
        if key_pressed[self.setting["KEY"]["SHOOT"]] and self.number > 0 and (time.time() - self.bullet_time) > 0.1:
            self.number -= 1
            self.bullet_time = time.time()
            return True
        else:
            return False
