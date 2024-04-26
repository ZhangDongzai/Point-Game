GAMEMODE_WELCOME = 0
GAMEMODE_RUNNING = 1
GAMEMODE_ENDING = 2

DATA = {
    "window": {
        "title": "Point Game",
        "size": (1280, 720),
        "color": (0, 0, 0),
        "fps": 0,
    },

    "player": {
        "radius": 20,
        "color": (255, 255, 255),
        "speed": 200,
    },

    "map": {
        "path": "data/map",
        "size": 40,
        "row": 18,
        "column": 32,
    },

    "fps_counter": {
        "size": 50,
        "color": (255, 255, 0),
    },

    "main_menu": {
        "title": {
            "size": 200,
            "color": (255, 255, 0),
            "mode": {
                GAMEMODE_WELCOME: "Point Game",
                GAMEMODE_ENDING: "END",
            },
        },
        "words": {
            "size": 50,
            "color": (255, 255, 255),
            "mode": {
                GAMEMODE_WELCOME: "Press any key to start.",
                GAMEMODE_ENDING: "Press any key to restart.",
            },
        }
    },
}

KEY = {
    "player": {
        1: {
            "forward": ord('w'),
            "backward": ord('s'),
            "left": ord('a'),
            "right": ord('d'),
        },
    },
}
