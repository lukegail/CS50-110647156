books = []

#add three books to your shelf
for _ in range(3):
    book = dict()
    book["title"] = input("Title: ").strip().capitalize()
    book["author"] = input("Author: ").strip().capitalize()

    books.append(book)
for book in books:
    print(book["title"])