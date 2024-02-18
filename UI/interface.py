# 开始、暂停、结束界面文件

import pygame

from setting import *


# 字体
class BaseFont(pygame.sprite.Sprite):
    color: tuple[int, int, int]
    size: int
    name: str

    def __init__(self, *groups) -> None:
        super().__init__(*groups)
        
        self.font = pygame.font.Font(None, size=self.size)
        self.image = None
        self.rect = None
        self.draw(text="")

    def draw(self, text: str) -> None:
        # 生成图像
        self.image = self.font.render(text, False, self.color)
        
        # 生成位置
        self.rect = self.image.get_rect()
        self.make_rect()

    def make_rect(self) -> None:
        pass


class Title(BaseFont):
    color = YELLOW
    size = int(250 * RATIO)
    name = "TITLE"

    def make_rect(self) -> None:
        self.rect.midbottom = SCREEN_CENTER


class Tip(BaseFont):
    color = WHITE
    size = int(50 * RATIO)
    name = "TIP"

    def make_rect(self) -> None:
        self.rect.midtop = SCREEN_CENTER
