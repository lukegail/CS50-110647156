// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>


bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    // valid function takes password as argument and returns a bool. if true, "password is valid"
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// function takes a string as argument and returns a bool
bool valid(string password)
{
    // these variables reflect presence of each type of char. bools default to false
    bool lower;
    bool upper;
    bool digit;
    bool punct;

    // iterates through each letter of password, each char type = 1 if present.
    for (int i = 0; password[i] != '\0'; i++)
    {
        if (islower(password[i]))
        {
            lower = 1;
        }
        else if (isupper(password[i]))
        {
            upper = 1;
        }
        else if (isdigit(password[i]))
        {
            digit = 1;
        }
        else if (ispunct(password[i]))
        {
            punct = 1;
        }
    }
    // if all conditions met (all char types present), returns true
    if (lower == 1 && upper == 1 && digit == 1 && punct == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
