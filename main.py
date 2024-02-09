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
        self.win = False

        # 精灵组
        self.ui = pygame.sprite.Group()
        self.sprite = pygame.sprite.Group()
        
        # 精灵
        self.map = maps.Map(game=self, _map=maps.map_1)
        self.ui_fps = UI.fps.FPS(self.ui, game=self)
        self.sprite_point_1 = sprites.point.Point(self.sprite, game=self, setting=PLAYER_1)
        self.sprite_point_2 = sprites.point.Point(self.sprite, game=self, setting=PLAYER_2)

        self.gameLoop()

    def gameLoop(self) -> None:
        while self.running:
            self.updateScreen()
            self.checkEvent()

    def checkEvent(self) -> None:
        for event in pygame.event.get():
            # 窗口关闭
            if event.type == pygame.QUIT:
                pygame.quit()
                self.running = False

    def updateScreen(self) -> None:
        # 更新帧间隔时间(单位: S)
        self.delta_time = self.clock.tick(SCREEN_FPS) / 1000
        
        # 更新
        self.ui.update()
        self.sprite.update()

        # 绘制屏幕
        self.screen.fill(color=SCREEN_COLOR)

        # 检测是否获胜
        if (len(self.sprite.sprites()) == 1) and (self.win == False):
            self.sprite.empty()
            self.ui.empty()
            UI.win.Win(self.ui)
            self.win = True
        else:
        # 绘制(地图 -> 角色附有 -> 角色 -> UI)
            self.map.draw()
            for sprite in self.sprite.sprites():
                self.screen.blit(sprite.image, sprite.rect)
                sprite.draw()
                
        for ui in self.ui.sprites():
            self.screen.blit(ui.image, ui.rect)

        # 更新缓存
        pygame.display.flip()


if __name__ == "__main__":
    Game()
