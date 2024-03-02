#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name? ");
    int age = get_int("How old are you? ");
    string phoneNumber = get_string("What is your phone number? ");

    printf("Name: %s\nAge: %i\nPhone Number: %s\n", name, age, phoneNumber);
}