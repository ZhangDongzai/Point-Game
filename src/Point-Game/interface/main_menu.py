import pygame

from config import *


class Button(pygame.sprite.Sprite):
    """A button of the menu."""

    size = DATA["main_menu"]["button"]["font_size"]
    magnification = DATA["main_menu"]["button"]["magnification"]
    color = DATA["main_menu"]["button"]["color"]

    def __init__(self, *groups, text: str, center: tuple[int, int]) -> None:
        super().__init__(*groups)

        self.small_font = pygame.Font(None, self.size)
        self.large_font = pygame.Font(None, int(self.size * self.magnification))
        self.small_image = self.small_font.render(text=text,
                                                  antialias=False,
                                                  color=self.color)
        self.large_image = self.large_font.render(text=text,
                                                  antialias=False,
                                                  color=self.color)
        self.small_rect = self.small_image.get_rect()
        self.large_rect = self.large_image.get_rect()
        self.small_rect.midtop = center
        self.large_rect.center = self.small_rect.center
        self.image, self.rect = self.small_image, self.small_rect

    def update(self) -> None:
        """Update the button's state."""
        # Determine if the mouse is on the button
        mouse_x, mouse_y = pygame.mouse.get_pos()
        if (self.rect.left < mouse_x < self.rect.right
            and self.rect.top < mouse_y < self.rect.bottom):
            self.image = self.large_image
            self.rect = self.large_rect
        else:
            self.image = self.small_image
            self.rect = self.small_rect
    

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
