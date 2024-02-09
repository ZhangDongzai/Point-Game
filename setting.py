# 游戏设置文件
import pygame
import math

# 颜色
BLACK = 0, 0, 0
WHITE = 255, 255, 255
YELLOW = 255, 255, 0
RED = 255, 0, 0

# 屏幕
SCREEN_TITLE = "Point Game"
SCREEN_SIZE = SCREEN_WIDTH, SCREEN_HEIGHT = 640, 360
SCREEN_COLOR = BLACK
SCREEN_FPS = 60

SCREEN_CENTER = SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2

# 图像比例
WIDTH_RATIO = SCREEN_WIDTH / 1280
HEIGHT_RATIO = SCREEN_HEIGHT / 720
RATIO = (WIDTH_RATIO + HEIGHT_RATIO) / 2

# 按键设置
PLAYER_1 = {
    "NUMBER": 1,
    "KEY": {
        "UP": pygame.K_w,
        "DOWN": pygame.K_s,
        "LEFT": pygame.K_a,
        "RIGHT": pygame.K_d,
        "SHOOT": pygame.K_j,
        "RELOAD_BULLET": pygame.K_k,
    },
    "POS": {
        "POINT": (80 * WIDTH_RATIO, 360 * HEIGHT_RATIO),
        "BULLET": (10 * WIDTH_RATIO, 10 * HEIGHT_RATIO),
    },
    "ANGLE": {
        "POINT": 0,
    },
}

PLAYER_2 = {
    "NUMBER": 2,
    "KEY": {
        "UP": pygame.K_UP,
        "DOWN": pygame.K_DOWN,
        "LEFT": pygame.K_LEFT,
        "RIGHT": pygame.K_RIGHT,
        "SHOOT": pygame.K_1,
        "RELOAD_BULLET": pygame.K_2,
    },
    "POS": {
        "POINT": (1200 * WIDTH_RATIO, 360 * HEIGHT_RATIO),
        "BULLET": (1180 * WIDTH_RATIO, 10 * HEIGHT_RATIO),
    },
    "ANGLE": {
        "POINT": math.pi,
    },
}
