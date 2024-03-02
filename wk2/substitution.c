#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// main takes CLA: 26-char encryption key
int main(int argc, string argv[])
{
// error messages if user input doesn't meet specs (one 26-char string)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain exactly 26 characters.\n");
        return 1;
    }

// key can't contain any non-alpha chars
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
    }

// key can only contain a letter exactly once
    int j, k;
    for (j = 0; j < 26; j++) // iterates 26 times (each character of the key)
    {
        for (k = 0; k < j; k++) // each character (j) is compared to the characters that went before (k)
        {
            if (tolower(argv[1][j]) == tolower(argv[1][k]))
            {
                printf("Key must contain each character exactly once.\n");
                return 1;
            }
        }
    }
// variable "key" initialized with user-input CLA (the 2nd word entered in CLI)
    string key = argv[1];

///// GET PLAINTEXT /////
// variable "plaintext" initialized with user-input (original message)
    string plaintext = get_string("plaintext: ");
    int n = strlen(plaintext);

///// CIPHER /////
// init ALPHA array with the alphabet
    const char ALPHA[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

// stores case of letters. (i used case_ because "case" is a reserved name (like if, while, etc))
    char case_[n];

// init ciphertext array of the same length as the user-input plaintext
// (the same number of chars as the original message)
    char ciphertext[n];

// this for loop iterates thru every letter of the original plaintext (plaintext[i]) and does the following:
//      1. detects case of letter (and assigns it to array case_[i])
//      2. changes case to lower before encrypting
//      3. finds the alphabetic number of the plaintext letter (and assigns it to variable "a")
//      4. populates the array "ciphertext" with corresponding "a" element of the key array
//      5. reverts case of letter back to original
    for (int i = 0; i < n; i++)
    {

// only encrypts alphabetic chars
        if (isalpha(plaintext[i]))
        {

// CASE detect (0 = lowercase, 1 = uppercase)
            if (islower(plaintext[i]))
            {
                case_[i] = 0;
            }
            if (isupper(plaintext[i]))
            {
                case_[i] = 1;
            }
// CASE lower (change case to lower before encrypting)
            plaintext[i] = tolower(plaintext[i]);

// iterate thru the alphabet until the letter matches plaintext[i], the letter from the plaintext message.
// (no need for "for" loop to have body if it's just counting)
// find the alphabetic number of the plaintext letter and assigns it to "a"
            int a;
            for (a = 0; ALPHA[a] != plaintext[i]; a++)
            {
            }
// populates the array "ciphertext" with corresponding "a" element of the key array
            ciphertext[i] = key[a];

// CASE revert (back to original)
            if (case_[i] == 0)
            {
                ciphertext[i] = tolower(ciphertext[i]);
            }
            else if (case_[i] == 1)
            {
                ciphertext[i] = toupper(ciphertext[i]);
            }
        }
// non alphabetic characters and spaces are left unchanged
        else
        {
            ciphertext[i] = plaintext[i];
        }
// had to add a \0 to the end of ciphertext or it would print wierd random chars at the end of ciphertext output.
        ciphertext[n] = '\0';
    }

///// PRINT CIPHER /////
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}



// i tried to distribute the cipher to a user-defined function but i couldn't because it couldn't return an array, or a string.
// i tried a couple work-arounds including adding \0 to the end, but ultimately found that the way to do this is
// to use pointers(?), which i havent learned yet. So i had to consolidate everything into main.