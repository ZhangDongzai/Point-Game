# 界面状态文件

from setting import *
import sprites

import pygame


class State:
    """界面状态类"""

    def __init__(self, game: object) -> None:
        self.game = game
        self.__number = 0
        self.number = 0

    @property
    def number(self) -> int:
        """界面代码
        0 - 开始界面  
        1 - 游戏界面  
        2 - 结束界面  
        3 - 暂停界面   
        """
        return self.__number

    @number.setter
    def number(self, number: int) -> None:
        self.__number = number

        # 开始界面
        if self.__number == 0:
            # 遍历每一个UI
            for ui in self.game.interface_ui.sprites():
                if ui.name == "TITLE":  # 标题
                    ui.draw(text="Point Game")
                elif ui.name == "TIP":  # 提示
                    ui.draw(text="Press any key to start")

        # 结束界面
        if self.__number == 2:
            # 遍历每一个UI
            for ui in self.game.interface_ui.sprites():
                if ui.name == "TITLE":  # 标题
                    ui.draw(text=f"Player {self.game.sprite.sprites()[0].setting["NUMBER"]} Win")
                elif ui.name == "TIP":  # 提示
                    ui.draw(text="Press any key to restart")

        # 暂停界面
        if self.__number == 3:
            # 遍历每一个UI
            for ui in self.game.interface_ui.sprites():
                if ui.name == "TITLE":  # 标题
                    ui.draw(text="Stop")
                elif ui.name == "TIP":  # 提示
                    ui.draw(text="Press any key to continue")

    def key_down(self) -> None:
        if self.__number == 0:  # 开始 -> 游戏
            self.number = 1
        elif self.__number == 1:  # 游戏
            if pygame.key.get_pressed()[pygame.K_ESCAPE]:  # 暂停
                self.number = 3
        elif self.__number == 2:  # 结束 -> 开始
            self.number = 0

            # 精灵重置
            self.game.sprite.empty()
            self.game.game_ui.empty()
            sprites.point.Point(self.game.sprite, game=self.game, setting=PLAYER_1)
            sprites.point.Point(self.game.sprite, game=self.game, setting=PLAYER_2)
        elif self.__number == 3:  # 暂停 -> 游戏
            self.number = 1
