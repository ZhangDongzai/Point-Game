import pygame

import config


class Player(pygame.sprite.Sprite):
    """Main character"""

    size = (config.DATA["player"]["radius"] * 2,) * 2

    def __init__(self, rect: pygame.Rect, *groups) -> None:
        super().__init__(*groups)

        self.image = pygame.Surface(size=self.size)
        self.rect = self.image.get_rect()

        self.rect.center = rect.center

        pygame.draw.circle(surface=self.image,
                           color=config.DATA["player"]["color"],
                           center=(config.DATA["player"]["radius"],
                                   config.DATA["player"]["radius"]),
                           radius=config.DATA["player"]["radius"])
