from math import cos, sin

import pygame

from config import *
import maps


INTERVAL_TIME = 0.1
last_time = 0



class Bullet(pygame.sprite.Sprite):
    """Player's weapon."""

    radius = DATA["bullet"]["radius"]
    size = (radius * 2,) * 2
    color = DATA["bullet"]["color"]
    speed = DATA["bullet"]["speed"]

    def __init__(self, *groups,
                 direction: float,
                 rect: pygame.Rect) -> None:
        super().__init__(*groups)

        self.image = pygame.Surface(size=self.size)
        self.rect = self.image.get_rect()
        self.x, self.y = self.rect.center = rect.center

        pygame.draw.circle(surface=self.image, color=self.color,
                           center=(self.radius,) * 2, radius=self.radius)
        
        self.speed_x = round(sin(direction), ACCURACY) * self.speed
        self.speed_y = round(cos(direction), ACCURACY) * self.speed


    def update(self, delta_time: int, maps: maps.Map) -> None:
        self.x = self.rect.centerx = self.x + self.speed_x * delta_time / 1000
        self.y = self.rect.centery = self.y + self.speed_y * delta_time / 1000

        if maps.check_collide(self.x, self.y):
            self.kill()
