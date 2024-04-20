import pygame

import config


COLOR = {
    0: "black",
    1: "white",
}


class Map(pygame.sprite.Sprite):
    """Map module"""
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
        with open(file=config.DATA["map"]["path"]) as file:
            text = file.readlines()
        for row, row_str in enumerate(text):
            for column, column_str in enumerate(row_str.rstrip("\n")):
                if int(column_str) != 0:
                    self.map[(row, column)] = int(column_str)
    
    def _draw(self) -> None:
        """Render image from map data."""
        for position, color_code in self.map.items():
            row, column = position
            rect = pygame.Rect(column*config.DATA["map"]["size"],
                               row*config.DATA["map"]["size"],
                               config.DATA["map"]["size"],
                               config.DATA["map"]["size"])
            pygame.draw.rect(surface=self.image,
                             color=COLOR[color_code],
                             rect=rect,
                             width=1)
            
    def check_collide(self, x: int, y: int) -> bool:
        """Check something collide or don't collide map."""
        row = y // config.DATA["map"]["size"]
        column = x // config.DATA["map"]["size"]
        return (row, column) in self.map
