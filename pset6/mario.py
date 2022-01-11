from cs50 import get_int

def main():
    # Get input
    height = get_height()
    draw(height)

def get_height():
    while True:
        height = get_int("Height: ")
        if height >= 1 and height <= 8:
            break
    return height

def draw(height):
    for row in range(1, height + 1):
        print(' ' * (height-row) + "#" * row + ' ' * 2 + "#" *row)
        

if __name__ == "__main__":
    main()

    