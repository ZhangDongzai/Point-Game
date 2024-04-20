import pygame

import config
import character.player
import map


class Game:
    def __init__(self) -> None:
        pygame.init()

        pygame.display.set_caption(config.DATA["window"]["title"])
        pygame.display.set_mode(size=config.DATA["window"]["size"])

        self.window = pygame.display.get_surface()
        self.clock = pygame.time.Clock()

        self.delta_time = 0

        self.player = character.player.Player()
        self.map = map.Map()

        self.run()

    def run(self) -> None:
        is_running = True
        while is_running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    is_running = False

            self.player.update(delta_time=self.delta_time, map=self.map)

            self.window.fill(color=config.DATA["window"]["color"])
            self.window.blit(source=self.map.image, dest=self.map.rect)
            self.window.blit(source=self.player.image, dest=self.player.rect)
            
            pygame.display.update()

            self.delta_time = self.clock.tick(config.DATA["window"]["fps"])

    def quit(self) -> None:
        pygame.quit()

    def __del__(self) -> None:
        self.quit()
