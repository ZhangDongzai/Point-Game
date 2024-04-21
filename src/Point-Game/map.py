import pygame

import config


COLOR = {
    0: "black",
    1: "white",
}


class Map(pygame.sprite.Sprite):
    """Map module"""

    path: str = config.DATA["map"]["path"]
    size: int = config.DATA["map"]["size"]

    def __init__(self, *groups) -> None:
        super().__init__(*groups)

        self.image = pygame.Surface(size=config.DATA["window"]["size"])
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
                if int(column_str) != 0:
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
        """Check something collide or don't collide map.

        Args:
            x: something's center position's x.
            y: something's center position's y.
        
        Returns:
            True if collide map, or False if don't collide map.
        """
        row = int(y // self.size)
        column = int(x // self.size)
        return (row, column) in self.map
