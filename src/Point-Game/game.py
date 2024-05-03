import pygame

from config import *
import character.player
import interface.fps_counter
import interface.main_menu
import maps


class Game:
    def __init__(self) -> None:
        pygame.init()

        pygame.display.set_caption(DATA["window"]["title"])
        pygame.display.set_mode(size=DATA["window"]["size"])

        self.window = pygame.display.get_surface()
        self.clock = pygame.time.Clock()

        self.fps_counter = interface.fps_counter.FPS_Counter()
        self.player = None
        self.maps = None
        self.main_menu = interface.main_menu.Main_Menu()

        self.delta_time = 0
        self._mode = -1
        self.mode = GAMEMODE_WELCOME

        self.run()

    def run(self) -> None:
        is_running = True
        while is_running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    is_running = False
                elif self.main_menu.button.check():
                    if self.mode == GAMEMODE_WELCOME:
                        self.mode = GAMEMODE_RUNNING
                    elif self.mode == GAMEMODE_ENDING:
                        self.mode = GAMEMODE_WELCOME

            self._render_game()
            self.delta_time = self.clock.tick(DATA["window"]["fps"])

    def quit(self) -> None:
        pygame.quit()

    @property
    def mode(self) -> int:
        """State of game"""
        return self._mode
    
    @mode.setter
    def mode(self, value: int) -> None:
        if self._mode == value:
            return
        self._mode = value

        if self.mode == GAMEMODE_WELCOME or self.mode == GAMEMODE_ENDING:
            self.main_menu.draw(game_mode=self.mode)
        elif self.mode == GAMEMODE_RUNNING:
            self.player = character.player.Player()
            self.maps = maps.Map()

    def _render_game(self) -> None:
        """Update and render screen."""
        self.window.fill(color=DATA["window"]["color"])
        self.fps_counter.update(fps=self.clock.get_fps())
        
        if self.mode == GAMEMODE_WELCOME or self.mode == GAMEMODE_ENDING:
            self.main_menu.update()
            self.window.blit(source=self.main_menu.image, dest=self.main_menu.rect)
        elif self.mode == GAMEMODE_RUNNING:
            self.player.update(delta_time=self.delta_time, maps=self.maps)

            self.window.blit(source=self.maps.image, dest=self.maps.rect)

            for bullet in self.player.bullets.sprites():
                self.window.blit(source=bullet.image, dest=bullet.rect)

            self.window.blit(source=self.player.image, dest=self.player.rect)

        self.window.blit(source=self.fps_counter.image, dest=self.fps_counter.rect)

        pygame.display.update()

    def __del__(self) -> None:
        self.quit()
