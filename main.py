# 游戏主文件

from setting import *
import sprites
import UI
import maps

import pygame


class Game:
    def __init__(self) -> None:
        # 初始化基类
        pygame.init()

        # 设置窗口
        pygame.display.set_caption(SCREEN_TITLE)
        pygame.display.set_mode(SCREEN_SIZE)
        self.screen = pygame.display.get_surface()

        # 时钟
        self.clock = pygame.time.Clock()
        self.delta_time = 1

        # 地图
        self.map = maps.Map(game=self, _map=maps.map_1)

        # 精灵组
        self.interface_ui = pygame.sprite.Group()
        self.game_ui = pygame.sprite.Group()
        self.sprite = pygame.sprite.Group()

        # 绘制
        self.draw()

        # 运行属性
        self.running = True
        self.state = UI.state.State(game=self)

        # 主循环     
        self.game_loop()

    def game_loop(self) -> None:
        while self.running:
            self.update_screen()
            self.check_event()

    def check_event(self) -> None:
        for event in pygame.event.get():
            # 窗口关闭
            if event.type == pygame.QUIT:
                pygame.quit()
                self.running = False

            # 按键
            elif event.type == pygame.KEYDOWN:
                self.state.key_down()

    def update_screen(self) -> None:
        # 更新帧间隔时间(单位: S)
        self.delta_time = self.clock.tick(SCREEN_FPS) / 1000

        # 更新
        self.game_ui.update()
        self.sprite.update()

        # 清空
        self.screen.fill(color=SCREEN_COLOR)

        # 绘制
        if self.state.number == 1:  # 游戏界面
            self.map.draw()  # 渲染地图

            for sprite in self.sprite.sprites():  # 绘制精灵
                self.screen.blit(sprite.image, sprite.rect)
                sprite.draw()

            for ui in self.game_ui.sprites():  # 绘制UI
                self.screen.blit(ui.image, ui.rect)
        else:  # 开始、暂停、结束界面
            for ui in self.interface_ui.sprites():  # 绘制UI
                self.screen.blit(ui.image, ui.rect)

        # 更新缓存
        pygame.display.flip()

    def draw(self) -> None:
        # UI
        UI.interface.Title(self.interface_ui)
        UI.interface.Tip(self.interface_ui)

        UI.fps.FPS(self.game_ui, game=self)

        # 精灵
        sprites.point.Point(self.sprite, game=self, setting=PLAYER_1)
        sprites.point.Point(self.sprite, game=self, setting=PLAYER_2)


if __name__ == "__main__":
    Game()
