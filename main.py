# 游戏主文件

from setting import *
from sprites import *

import pygame
import sys


class Game:
    def __init__(self) -> None:
        pygame.init()
        pygame.display.set_caption(SCREEN_TITLE)        # 设置标题
        pygame.display.set_mode(SCREEN_SIZE)            # 设置大小

        self.screen = pygame.display.get_surface()
        self.clock = pygame.time.Clock()
        self.delta_time = 1

        # 角色
        self.sprite_point = Point(game=self)

        self.gameLoop()

    def gameLoop(self) -> None:
        while True:
            self.checkEvent()
            self.updateScreen()

    def checkEvent(self) -> None:
        for event in pygame.event.get():
            # 窗口关闭
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

    def updateScreen(self) -> None:
        # 更新时钟和帧间隔时间(单位: S)
        self.delta_time = self.clock.tick(SCREEN_FPS) / 1000

        # 绘制屏幕和角色
        self.screen.fill(color=SCREEN_COLOR)
        self.sprite_point.update()
        self.screen.blit(self.sprite_point.image, self.sprite_point.rect)

        # 更新缓存
        pygame.display.flip()


if __name__ == "__main__":
    Game()
