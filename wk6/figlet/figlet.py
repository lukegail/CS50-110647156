"""
Figlet Font Generator
https://cs50.harvard.edu/x/2023/problems/6/figlet/

This Python script transforms text input into ASCII art using the Figlet font system.
It accepts zero or two additional command-line arguments (CLI args).

Usage:
1. Run the script without additional CLI args to randomly select a Figlet font for the text transformation.
    Example: python script_name.py
2. Run the script with two additional CLI args where the first argument is '-f' or '--font' and the second is the name of the Figlet font you want to use.
    Example: python script_name.py -f slant

available fonts: http://www.figlet.org/examples.html

The script will prompt the user for the text to be transformed and will output the resulting text in the selected Figlet font.
"""

from sys import argv, exit
from pyfiglet import Figlet
from random import randint


# CHECK COMMAND-LINE ARGUMENTS
# Count the number of CLI args
num_args = len(argv)

# exit if not zero or two additional CLI args
if num_args != 1 and num_args != 3:
    print('Invalid usage')
    exit(1)

# exit if the first additional arg is NOT either '-f' or '--font'
if num_args == 3 and (argv[1] != '-f' and argv[1] != '--font'):
    print('Invalid usage')
    exit(1)


# INITIALIZE FIGLET FONT OBJECT AND RETRIEVE AVAILABLE FONTS
# Create an instance of the Figlet class, initializing a Figlet font object for text transformation
figlet = Figlet()

# Retrieve the list of available fonts
font_list = figlet.getFonts()


# SELECTED FONT
# randomly select font if no additional CLI args
if num_args == 1:
    selected_font = font_list[randint(0, len(font_list) - 1)]
    figlet.setFont(font=selected_font)

# use the specified font 2 additional args are used and the 2nd is a valid font
if num_args == 3:
    if argv[2] not in font_list:
        print('Invalid usage')
        exit(1)
    else:
        figlet.setFont(font=argv[2])


# GET USER INPUT, OUTPUT FIGLET TEXT
# Prompt the user for text input
user_input = input('Input: ').strip()

# Output the text in figlet font.
print('Output: ')
print(figlet.renderText(user_input))

