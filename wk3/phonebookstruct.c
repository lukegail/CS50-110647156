#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Here we're declaring a new data type called 'person'.
// This is a structure type, so it can contain multiple other types.
// In this case, a 'person' contains a name and a number, both of which are strings.
typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];

    // We're assigning the name and number of the first person
    people[0].name = "Katie";
    people[0].number = "802-989-3001";

    people[1].name = "Luke";
    people[1].number = "802-498-8788";

    string name = get_string("Name: ");
    for (int i = 0; i < 2; i++)
    {
        // note the people[i].name and people[i].number
        if (strcmp(name, people[i].name) == 0)
        {
            printf("Found: %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}