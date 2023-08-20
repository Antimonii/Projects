#include <iostream>
#include <vector>
#include <string>
#include <map>

class Book {
public:
    Book(const std::string& title, const std::string& author)
        : title(title), author(author), available(true) {}

    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    bool isAvailable() const {
        return available;
    }

    void borrowBook() {
        if (available) {
            available = false;
            std::cout << "Book borrowed." << std::endl;
        } else {
            std::cout << "Book is not available for borrowing." << std::endl;
        }
    }

    void returnBook() {
        if (!available) {
            available = true;
            std::cout << "Book returned." << std::endl;
        } else {
            std::cout << "Book is already available." << std::endl;
        }
    }

private:
    std::string title;
    std::string author;
    bool available;
};

class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void listBooks() const {
        std::cout << "Books in the library:" << std::endl;
        for (const Book& book : books) {
            std::cout << "Title: " << book.getTitle() << " | Author: " << book.getAuthor();
            if (book.isAvailable()) {
                std::cout << " | Available" << std::endl;
            } else {
                std::cout << " | Not Available" << std::endl;
            }
        }
    }

    void borrowBook(const std::string& title) {
        for (Book& book : books) {
            if (book.getTitle() == title) {
                book.borrowBook();
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    void returnBook(const std::string& title) {
        for (Book& book : books) {
            if (book.getTitle() == title) {
                book.returnBook();
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

private:
    std::vector<Book> books;
};

int main() {
    Library library;

    Book book1("The Great Gatsby", "F. Scott Fitzgerald");
    Book book2("To Kill a Mockingbird", "Harper Lee");
    Book book3("1984", "George Orwell");

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);

    while (true) {
        std::cout << "Library Management System" << std::endl;
        std::cout << "1. List Books" << std::endl;
        std::cout << "2. Borrow Book" << std::endl;
        std::cout << "3. Return Book" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            library.listBooks();
        } else if (choice == 2) {
            std::cout << "Enter the title of the book to borrow: ";
            std::string title;
            std::cin.ignore(); // Clear newline character from previous input
            std::getline(std::cin, title);
            library.borrowBook(title);
        } else if (choice == 3) {
            std::cout << "Enter the title of the book to return: ";
            std::string title;
            std::cin.ignore(); // Clear newline character from previous input
            std::getline(std::cin, title);
            library.returnBook(title);
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }

    return 0;
}
