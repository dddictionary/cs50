from cs50 import get_string


def main():
    text = get_string("Text: ")
    grade = round(index(text))
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade: {grade}")

def count_letters(text):
    c = 0
    for i in text:
        if i.isalpha():
            c += 1
    return c

def count_words(text):
    words = 1
    for i in text:
        if i == ' ':
            words += 1
    return words

def count_sentences(text):
    sentences = 0
    for i in text:
        if i in ['.', '!', '?']:
            sentences += 1
    return sentences

def index(text):
    grade = 0
    L = count_letters(text) * 100 / count_words(text)
    S = count_sentences(text) * 100 / count_words(text)

    grade = 0.0588 * L - 0.296 * S - 15.8

    return grade

if __name__ == "__main__":
    main()