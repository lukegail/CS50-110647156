#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string names[] = {"Katie", "Luke"};
    string numbers[] = {"+1-802-989-3001", "+1-802-498-8788"};

    string name = get_string("Name: ");
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(name, names[i]) == 0)
        {
            printf("Found: %s\n", numbers[i]);
            return 0;

        }

    }
    printf("Not found\n");
    return 1;
}