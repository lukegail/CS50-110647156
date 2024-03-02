import nltk

nltk.download("punkt")
from nltk.tokenize import sent_tokenize
from cs50 import get_string


# count number of letters in text
def count_letters(text):
    letters = 0
    for char in text:
        if char.isalpha():
            letters += 1
    return letters


# count number of words in text
def count_words(text):
    words = 1
    for char in text:
        if char.isspace():
            words += 1
    return words


# count number of sentences in text
def count_sentences(text):
    sentence_list = sent_tokenize(text)
    return len(sentence_list)


# calculate coleman-liau index (grade level) of text
def coleman_liau(let, wor, sen):
    L = let / wor * 100
    S = sen / wor * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    return index


def main():
    # get text from user
    text = get_string("Text: ")

    # get counts of letters, words, and sentences in the text
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # get grade-level
    index = coleman_liau(letters, words, sentences)

    # print grade level
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
