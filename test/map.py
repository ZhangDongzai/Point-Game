with open("data/map", "rb") as file:
    for i in file.read():
        print(chr(i), end=" ")