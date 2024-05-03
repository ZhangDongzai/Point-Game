import pygame

from config import *


class Button(pygame.sprite.Sprite):
    """A button of the menu."""

    font_size = DATA["main_menu"]["button"]["font_size"]
    magnification = DATA["main_menu"]["button"]["magnification"]
    color = DATA["main_menu"]["button"]["color"]

    def __init__(self, *groups, text: str, center: tuple[int, int]) -> None:
        super().__init__(*groups)

        self.font = pygame.Font(None, self.font_size)
        self.image = self.font.render(text=text, antialias=False,
                                      color=self.color)
        self.rect = self.image.get_rect()
        self.rect.midtop = self.x, self.y = center
        self.size = self.width, self.height = self.rect.size

    def update(self) -> None:
        """Update the button's state."""
        # Determine if the mouse is on the button
        mouse_x, mouse_y = pygame.mouse.get_pos()
        if (self.rect.left < mouse_x < self.rect.right
            and self.rect.top < mouse_y < self.rect.bottom):
            self.size = (self.width*self.magnification, self.height*self.magnification)
        elif (self.width, self.height) != self.size:
            self.size = self.width, self.height
        self.image = pygame.transform.scale(surface=self.image, size=self.size)
        self.rect = self.image.get_rect()
        self.rect.midtop = self.x, self.y

    def check(self) -> bool:
        """Determine if the mouse is pressed"""
        mouse_x, mouse_y = pygame.mouse.get_pos()
        return (self.rect.left < mouse_x < self.rect.right
                and self.rect.top < mouse_y < self.rect.bottom
                and pygame.mouse.get_pressed()[0])


class Main_Menu(pygame.sprite.Sprite):
    """Main menu of game."""

    def __init__(self, *groups) -> None:
        super().__init__(*groups)

        self.image = pygame.Surface(size=DATA["window"]["size"])
        self.rect = self.image.get_rect()

        self.title_image = None
        self.title_rect = None
        self.title_font = pygame.Font(None, DATA["main_menu"]["title"]["size"])

        self.button = Button(text="Start", center=self.rect.center)

    def update(self) -> None:
        """Update words on image."""
        self.image.fill((0, 0, 0))
        self.button.update()
        self.image.blit(source=self.title_image, dest=self.title_rect)
        self.image.blit(source=self.button.image, dest=self.button.rect)

    def draw(self, game_mode: int) -> None:
        self.title_image = self.title_font.render(text=DATA["main_menu"]["title"]["mode"][game_mode],
                                                  antialias=False,
                                                  color=DATA["main_menu"]["title"]["color"])
        self.title_rect = self.title_image.get_rect()
        self.title_rect.midbottom = self.rect.center
