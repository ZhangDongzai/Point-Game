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
                 direction: list[DirectionType],
                 rect: pygame.Rect) -> None:
        super().__init__(*groups)

        self.image = pygame.Surface(size=self.size)
        self.rect = self.image.get_rect()
        self.x, self.y = self.rect.center = rect.center
        self.speed_x, self.speed_y = 0, 0

        pygame.draw.circle(surface=self.image, color=self.color,
                           center=(self.radius,) * 2, radius=self.radius)
        
        match direction[0]:
            case "forward":
                self.speed_y = -self.speed
            case "backward":
                self.speed_y = self.speed
        match direction[1]:
            case "left":
                self.speed_x = -self.speed
            case "right":
                self.speed_x = self.speed
        if self.speed_x and self.speed_y:
            self.speed_x *= COS45
            self.speed_y *= COS45


    def update(self, delta_time: int, maps: maps.Map) -> None:
        self.x = self.rect.centerx = self.x + self.speed_x * delta_time / 1000
        self.y = self.rect.centery = self.y + self.speed_y * delta_time / 1000

        if maps.check_collide(self.x, self.y):
            self.kill()
