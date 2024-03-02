#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

float calc_hours(int hours[], int weeks, char output)
{
// total up the hours saved in the array into a new variable.
    float total = 0;
    for (int j = 0; j < weeks; j++)
    {
        total += hours[j];
    }
// depending on the value of output, return either this sum, or the average number of hours.
    if (output == 'T')
    {
        return total;
    }
    else
    {
        return (total / weeks);
    }
}