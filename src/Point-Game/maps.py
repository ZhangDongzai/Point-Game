import pygame

from config import *


EMPTY_COLOR = 0
COLOR = {
    1: "white",
}


class Map(pygame.sprite.Sprite):
    """Map module"""

    path: str = DATA["map"]["path"]
    size: int = DATA["map"]["size"]

    def __init__(self, *groups) -> None:
        super().__init__(*groups)

        self.image = pygame.Surface(size=DATA["window"]["size"])
        self.rect = self.image.get_rect()

        self.map: dict[tuple, int] = {}
        self.rects: list[pygame.Rect] = []
        self._load()
        self._draw()
    
    def _load(self) -> None:
        """Load data from `map` file."""
        with open(file=self.path) as file:
            text = file.readlines()
        for row, row_str in enumerate(text):
            for column, column_str in enumerate(row_str.rstrip("\n")):
                if int(column_str) != EMPTY_COLOR:
                    self.map[(row, column)] = int(column_str)
    
    def _draw(self) -> None:
        """Render image from map data."""
        for position, color_code in self.map.items():
            row, column = position
            rect = pygame.Rect(column*self.size, row*self.size,
                               self.size, self.size)
            pygame.draw.rect(surface=self.image, color=COLOR[color_code],
                             rect=rect, width=1)
            
    def check_collide(self, x: float, y: float) -> bool:
        """Check sprite collide or don't collide map.

        Args:
            x: sprite's center position's x.
            y: sprite's center position's y.
        
        Returns:
            sprite collide map or not.
        """
        row = int(y // self.size)
        column = int(x // self.size)
        return (row, column) in self.map
