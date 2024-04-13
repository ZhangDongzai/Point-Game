import pygame

import config


class Player(pygame.sprite.Sprite):
    """Main character"""

    size = (config.DATA["player"]["radius"] * 2,) * 2
    speed = config.DATA["player"]["speed"]
    color = config.DATA["player"]["color"]
    radius = config.DATA["player"]["radius"]

    def __init__(self, *groups) -> None:
        super().__init__(*groups)

        self.image = pygame.Surface(size=self.size)
        self.rect = self.image.get_rect()

        self.image.set_colorkey("black")
        self.rect.center = (config.DATA["window"]["size"][0] / 2,
                            config.DATA["window"]["size"][1] / 2)
        self.x, self.y = self.rect.center
        pygame.draw.circle(surface=self.image,
                           color=self.color,
                           center=(config.DATA["player"]["radius"],
                                   config.DATA["player"]["radius"]),
                           radius=self.radius)
        
    def update(self, delta_time: int) -> None:
        """Update player's position.
        
        Args:
            delta_time: ms
        """
        key_state = pygame.key.get_pressed()
        x, y = 0, 0

        # Check keys
        if key_state[config.KEY["player"][1]["forward"]]:
            y -= self.speed * delta_time / 1000
        if key_state[config.KEY["player"][1]["backward"]]:
            y += self.speed * delta_time / 1000
        if key_state[config.KEY["player"][1]["right"]]:
            x += self.speed * delta_time / 1000
        if key_state[config.KEY["player"][1]["left"]]:
            x -= self.speed * delta_time / 1000

        # Press both two keys
        if x and y:
            x *= 0.7071
            y *= 0.7071

        self.rect.center = self.x, self.y = self.x + x, self.y + y
