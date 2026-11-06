#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

using namespace std;

class Book
{
public:
    // Genre enumeration
    enum Genre
    {
        fiction,
        nonfiction,
        periodical,
        biography,
        children
    };

private:
    string ISBN;
    string title;
    string author;
    int copyrightDate;
    bool checkedOut;
    Genre genre;

public:
    // Default constructor
    Book();

    // Parameterized constructor
    Book(string isbn,
         string title,
         string author,
         int copyrightDate,
         Genre genre);

    // Getter functions
    string getISBN() const;
    string getTitle() const;
    string getAuthor() const;
    int getCopyrightDate() const;
    bool isCheckedOut() const;
    Genre getGenre() const;

    // Check out book
    void checkOut();

    // Check in book
    void checkIn();

    // Operator overloading
    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;

    // Friend output operator
    friend ostream& operator<<(ostream& os, const Book& book);
};

#endif