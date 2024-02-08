# 游戏主文件

from setting import *
import sprites
import UI
import maps

import pygame


class Game:
    def __init__(self) -> None:
        # 初始化pygame
        pygame.init()

        # 设置窗口属性
        pygame.display.set_caption(SCREEN_TITLE)        # 设置标题
        pygame.display.set_mode(SCREEN_SIZE)            # 设置大小

        self.running = True
        self.screen = pygame.display.get_surface()
        self.clock = pygame.time.Clock()
        self.delta_time = 1

        # 角色组
        self.ui = pygame.sprite.Group()
        self.sprite = pygame.sprite.Group()
        
        # 角色
        self.map = maps.Map(game=self, _map=maps.map_1)
        self.ui_fps = UI.fps.FPS(self.ui, game=self)
        self.ui_bullet = UI.bullet.Bullet(self.ui, game=self)
        self.sprite_point = sprites.point.Point(self.sprite, game=self)

        self.gameLoop()

    def gameLoop(self) -> None:
        while self.running:
            self.updateScreen()
            self.checkEvent()

    def checkEvent(self) -> None:
        for event in pygame.event.get():
            # 窗口关闭
            if event.type == pygame.QUIT:
                pygame.base.quit()
                self.running = False

    def updateScreen(self) -> None:
        # 更新帧间隔时间(单位: S)
        self.delta_time = self.clock.tick(SCREEN_FPS) / 1000
        
        # 更新
        self.ui.update()
        self.sprite.update()

        # 绘制屏幕
        self.screen.fill(color=SCREEN_COLOR)

        # 绘制(地图 -> 角色附有 -> 角色 -> UI)
        self.map.draw()
        self.sprite_point.draw()
        self.screen.blit(self.sprite_point.image, self.sprite_point.rect)
        self.screen.blit(self.ui_fps.image, self.ui_fps.rect)
        self.screen.blit(self.ui_bullet.image, self.ui_bullet.rect)

        # 更新缓存
        pygame.display.flip()


if __name__ == "__main__":
    Game()
