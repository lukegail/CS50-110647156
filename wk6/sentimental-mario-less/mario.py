from cs50 import get_int

# gets height of pyramid from user, accepting 1-8
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# for each row up to user-specified height
for row in range(height):
    # print spaces before pyramid
    print(" " * (height - 1 - row), end="")

    # print hashes
    print("#" * (row + 1), end="")

    # new line after each row
    print()
