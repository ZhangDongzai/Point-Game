import pygame

import config


MAP_COLOR = {
    0: "black",
    1: "white",
}


class Map:
    """Display map"""

    def __init__(self, path: str) -> None:
        self.__map = []
        self.load(path)

    @property
    def map(self) -> list[list[int]]:
        """Return a 2D map."""
        return self.__map
    
    def load(self, path: str) -> None:
        """Load a map from a file."""
        with open(file=path, mode="br") as file:
            row, column = 0, 0
            for byte in file.read():
                if len(self.__map) != row + 1:
                    self.__map.append([])
                self.__map[-1].append(byte)
                column += 1
                if column >= config.DATA["map"]["column"]:
                    row, column = row + 1, 0

        # Check map size
        if len(self.__map) != config.DATA["map"]["row"]:
            assert "Map size is wrong."
        for row in self.__map:
            if len(row) != config.DATA["map"]["column"]:
                assert "Map size is wrong."

    def draw(self, window: pygame.Surface) -> None:
        """Draw the image."""
        for row in range(config.DATA["map"]["row"]):
            for column in range(config.DATA["map"]["column"]):
                rect = pygame.Rect(row * config.DATA["map"]["size"],
                                   column * config.DATA["map"]["size"],
                                   config.DATA["map"]["size"],
                                   config.DATA["map"]["size"])
                color = MAP_COLOR[int(chr(self.__map[row][column]))]
                pygame.draw.rect(surface=window,
                                 color=color,
                                 rect=rect,
                                 width=1)
