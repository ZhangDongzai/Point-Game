# 开始界面

from setting import *

import pygame


class Title(pygame.sprite.Sprite):
	color = YELLOW
	size = int(250 * RATIO)

	def __init__(self, *groups) -> None:
		super().__init__(*groups)

		self.font = pygame.font.Font(None, size=self.size)

		self.image = self.font.render("Point Game", False, self.color)
		
		self.rect = self.image.get_rect()
		self.rect.midbottom = SCREEN_CENTER


class Tip(pygame.sprite.Sprite):
	color = WHITE
	size = int(50 * RATIO)

	def __init__(self, *groups) -> None:
		super().__init__(*groups)

		self.font = pygame.font.Font(None, size=self.size)

		self.image = self.font.render("Press any key to start", False, self.color)
		
		self.rect = self.image.get_rect()
		self.rect.midtop = SCREEN_CENTER
