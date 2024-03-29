// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

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

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    float total_tax = bill * tax / 100;
    float total_tip = (bill + total_tax) * tip / 100;
    float total_bill = (bill + total_tax + total_tip);
    return total_bill / 2;
}
