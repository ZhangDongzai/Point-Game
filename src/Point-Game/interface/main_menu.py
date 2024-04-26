import pygame

from config import *


class Main_Menu(pygame.sprite.Sprite):
    """Main menu of game."""

    def __init__(self, *groups) -> None:
        super().__init__(*groups)

        self.image = pygame.Surface(size=DATA["window"]["size"])
        self.rect = self.image.get_rect()

        self.title_image = None
        self.title_rect = None
        self.title_font = pygame.Font(None, DATA["main_menu"]["title"]["size"])

        self.words_image = None
        self.words_rect = None
        self.words_font = pygame.Font(None, DATA["main_menu"]["words"]["size"])

    def update(self, game_mode: int) -> None:
        """Update words on image."""
        self.title_image = self.title_font.render(text=DATA["main_menu"]["title"]["mode"][game_mode],
                                                  antialias=False,
                                                  color=DATA["main_menu"]["title"]["color"])
        self.words_image = self.words_font.render(text=DATA["main_menu"]["words"]["mode"][game_mode],
                                                  antialias=False,
                                                  color=DATA["main_menu"]["words"]["color"])
        
        self.title_rect = self.title_image.get_rect()
        self.words_rect = self.words_image.get_rect()

        self.title_rect.midbottom = self.rect.center
        self.words_rect.midtop = self.rect.center
        
        self.image.blit(source=self.title_image, dest=self.title_rect)
        self.image.blit(source=self.words_image, dest=self.words_rect)
