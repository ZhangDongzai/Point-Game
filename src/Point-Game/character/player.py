import time

import pygame

from config import *
import maps
import character.bullet


class Player(pygame.sprite.Sprite):
    """Main character"""

    size = (DATA["player"]["radius"] * 2,) * 2
    speed = DATA["player"]["speed"]
    color = DATA["player"]["color"]
    radius = DATA["player"]["radius"]

    def __init__(self, *groups) -> None:
        super().__init__(*groups)

        self.image = pygame.Surface(size=self.size)
        self.rect = self.image.get_rect()
        self.direction: list[DirectionType] = ["forward", None]
        self.bullets = pygame.sprite.Group()

        self.image.set_colorkey("black")
        self.rect.center = (DATA["window"]["size"][0] / 2,
                            DATA["window"]["size"][1] / 2)
        self.x, self.y = self.rect.center
        pygame.draw.circle(surface=self.image,
                           color=self.color,
                           center=(DATA["player"]["radius"],
                                   DATA["player"]["radius"]),
                           radius=self.radius)
        
    def update(self, delta_time: int, maps: maps.Map) -> None:
        """Update player's position.
        
        Args:
            delta_time: ms
            maps: a Map object
        """
        key_state = pygame.key.get_pressed()
        x, y = 0, 0
        direction: list[DirectionType] = [None, None]

        # Check keys
        if key_state[KEY["player"][1]["forward"]]:
            y -= self.speed * delta_time / 1000
            direction[0] = "forward"
        if key_state[KEY["player"][1]["backward"]]:
            y += self.speed * delta_time / 1000
            direction[0] = "backward"
        if key_state[KEY["player"][1]["right"]]:
            x += self.speed * delta_time / 1000
            direction[1] = "right"
        if key_state[KEY["player"][1]["left"]]:
            x -= self.speed * delta_time / 1000
            direction[1] = "left"
        if direction[0] or direction[1]:
            self.direction = direction
        if (key_state[KEY["player"][1]["launch"]]
            and time.time() - character.bullet.last_time 
            > character.bullet.INTERVAL_TIME):
            character.bullet.last_time = time.time()
            character.bullet.Bullet(self.bullets,
                                    direction=self.direction,
                                    rect=self.rect)

        # Move to two directions
        if x and y:
            x *= 0.7071
            y *= 0.7071
        
        # Check collide
        if not maps.check_collide(self.x + x, self.y):
            self.rect.centerx = self.x = self.x + x
        if not maps.check_collide(self.x, self.y + y):
            self.rect.centery = self.y = self.y + y

        self.bullets.update(delta_time, maps)

    def _launch(self) -> None:
        pass
