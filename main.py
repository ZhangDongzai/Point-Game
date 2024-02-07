# 游戏主文件

from setting import *
import sprites.point
import UI.fps
import maps.map_1

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

        # 角色组
        self.ui = pygame.sprite.Group()
        self.sprite = pygame.sprite.Group()
        
        # 角色
        self.map = maps.map_1.Map(game=self)
        self.ui_fps = UI.fps.FPS(self.ui, game=self)
        self.ui_bullet = UI.bullet.Bullet(self.ui, game=self)
        self.sprite_point = sprites.point.Point(self.sprite, game=self)

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
        # 更新帧间隔时间(单位: S)
        self.delta_time = self.clock.tick(SCREEN_FPS) / 1000
        
        # 更新角色
        self.map.update()
        self.ui.update()
        self.sprite.update()

        # 绘制屏幕
        self.screen.fill(color=SCREEN_COLOR)

        # 绘制(地图 -> 角色附有 -> 角色 -> UI)
        self.screen.blit(self.map.image, self.map.rect)
        self.sprite_point.draw()
        self.screen.blit(self.sprite_point.image, self.sprite_point.rect)
        self.screen.blit(self.ui_fps.image, self.ui_fps.rect)
        self.screen.blit(self.ui_bullet.image, self.ui_bullet.rect)

        # 更新缓存
        pygame.display.flip()


if __name__ == "__main__":
    Game()
