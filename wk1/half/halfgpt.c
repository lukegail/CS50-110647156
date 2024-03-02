#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill = get_float("Bill before tax and tip: ");
    float tax = get_float("Sale Tax Percent: ");
    int tip = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill, tax, tip));
}

// this does the thing
float half(float bill, float tax, int tip)
{
    float total_tax = bill * tax / 100;
    float total_tip = bill * tip / 100;
    float total_bill = bill + total_tax + total_tip;
    return total_bill / 2;
}
