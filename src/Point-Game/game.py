import pygame

import config
import character.player
import interface.fps_counter
import map


GAMEMODE_WELCOME = 0
GAMEMODE_RUNNING = 1
GAMEMODE_ENDING = 2


class Game:
    def __init__(self) -> None:
        pygame.init()

        pygame.display.set_caption(config.DATA["window"]["title"])
        pygame.display.set_mode(size=config.DATA["window"]["size"])

        self.window = pygame.display.get_surface()
        self.clock = pygame.time.Clock()

        self.fps_counter = interface.fps_counter.FPS_Counter()
        self.player = None
        self.map = None

        self.delta_time = 0
        self._mode = -1
        self.mode = GAMEMODE_RUNNING

        self.run()

    def run(self) -> None:
        is_running = True
        while is_running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    is_running = False

            self._render_game()
            self.delta_time = self.clock.tick(config.DATA["window"]["fps"])

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

        if self._mode == GAMEMODE_WELCOME:
            pass
        elif self._mode == GAMEMODE_RUNNING:
            self.player = character.player.Player()
            self.map = map.Map()
        elif self._mode == GAMEMODE_ENDING:
            pass

    def _render_game(self) -> None:
        """Update and render screen."""
        self.window.fill(color=config.DATA["window"]["color"])
        self.fps_counter.update(fps=self.clock.get_fps())
        
        if self.mode == GAMEMODE_WELCOME:
            pass
        elif self.mode == GAMEMODE_RUNNING:
            self.player.update(delta_time=self.delta_time, map=self.map)

            self.window.blit(source=self.map.image, dest=self.map.rect)
            self.window.blit(source=self.player.image, dest=self.player.rect)
        elif self.mode == GAMEMODE_ENDING:
            pass

        self.window.blit(source=self.fps_counter.image, dest=self.fps_counter.rect)

        pygame.display.update()

    def __del__(self) -> None:
        self.quit()
