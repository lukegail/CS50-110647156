#include <cs50.h>
#include <stdio.h>
#include <string.h>

// checks to see if the letter in a user-input word are alphabetically ordered

int main(void)
{
	string word = get_string("word: ");
	int length = strlen(word);
	for (int i = 0; i < length - 1; i++)
	{
		if (word[i] < word[i + 1])
		{
			printf("Are %c & %c in order? YES\n", word[i], word[i + 1]);
		}
		else
		{
			printf("Are %c & %c in order? NO\n", word[i], word[i + 1]);
		}
	}
}