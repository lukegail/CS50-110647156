#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long card = get_long("Number: ");
    if (card >= 5800000000000000 || card < 4000000000000)
    {
        printf("INVALID\n");
        return 0;
    }

    // first pass
    // finds 2nd digit from the end
    long a = card;
    int b, c, d;
    int sum = 0;

    a = a / 10;
    b = a % 10;
    c = b * 2;
    d = c % 10;
    if (c >= 10)
    {
        sum++;
    }
    sum = sum + d;

    // finds every other digit
    for (int i = 0; a > 10; i++)
    {
        a = a / 100;
        b = a % 10;
        c = b * 2;
        d = c % 10;
        if (c >= 10)
        {
            sum++;
        }
        sum = sum + d;
    }

    // second pass
    // finds last digit
    b = card % 10;
    sum = sum + b;

    // finds every other digit
    a = card;
    for (int i = 0; a > 0; i++)
    {
        a = a / 100;
        b = a % 10;

        sum = sum + b;
    }

    // pass checksum and print card type
    if (sum % 10 == 0)
    {
        if ((card >= 340000000000000 && card <= 350000000000000) || (card >= 370000000000000 && card <= 380000000000000))
        {
            printf("AMEX\n");
        }
        else if (card >= 5100000000000000 && card <= 5600000000000000)
        {
            printf("MASTERCARD\n");
        }
        else if ((card >= 4000000000000 && card <= 5000000000000) || (card >= 4000000000000000 && card <= 5000000000000000))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}