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
