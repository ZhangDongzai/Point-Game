# 开始、暂停、结束界面文件

import pygame

from setting import *


# 字体
class BaseFont(pygame.sprite.Sprite):
    color: tuple[int, int, int]
    size: int

    def __init__(self, *groups, text: str) -> None:
        super().__init__(*groups)
        
        self.text = text
        self.font = pygame.font.Font(None, size=self.size)

        self.draw()
        self.makeRect()

    def draw(self) -> None:
        # 生成图像
        self.image = self.font.render(self.text, False, self.color)
        
        # 生成位置
        self.rect = self.image.get_rect()

    def makeRect(self) -> None:
        pass


class Title(BaseFont):
    color = YELLOW
    size = int(250 * RATIO)

    def makeRect(self) -> None:
        self.rect.midbottom = SCREEN_CENTER


class Tip(BaseFont):
    color = WHITE
    size = int(50 * RATIO)

    def makeRect(self) -> None:
        self.rect.midtop = SCREEN_CENTER
