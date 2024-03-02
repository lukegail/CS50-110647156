# Welcome to Felipe's Taqueria!
# To place an order, enter the name of the menu item you'd like.
# To finish ordering and exit the program, press Ctrl-d.

# Create menu dictionary
menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

# Print the menu with aligned prices
print("\nMENU")
for item, price in menu.items():
    print(f"{item}: {' ' * (16 - len(item))}${price:.2f}")  # Add padding to keep prices aligned

print("\nWhat would you like to order?")

# Initialize the total cost
total = 0.0

# Main ordering loop
try:
    while True:

        # prompt user to order an item by name
        item = input("Item: ").title()  # Converts Input To Titlecase

        # check if the item is on the menu
        if item in menu:

            # Add the price of the item to the total cost
            total += menu[item]

            # print total price, formatted to 2 decimal places
            print(f"Total: ${total:.2f}")

        # Ignore invalid items
        else:
            pass

# Handle Ctrl-D (EOFError) to exit the program
except EOFError:
    print()  # Move the cursor to the next line