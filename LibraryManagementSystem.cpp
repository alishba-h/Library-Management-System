#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ============================
// 1. Book Class
// ============================
class Book {
private:
    string title;
    string author;
    int bookID;
    bool isAvailable;

public:
    // Constructor
    Book(int id, string t, string a) {
        bookID = id;
        title = t;
        author = a;
        isAvailable = true;
    }

    // Getters
    int getID() { return bookID; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    bool getAvailability() { return isAvailable; }

    // Methods
    void borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            cout << "? Book \"" << title << "\" borrowed successfully!" << endl;
        } else {
            cout << "? Book \"" << title << "\" is already borrowed!" << endl;
        }
    }

    void returnBook() {
        if (!isAvailable) {
            isAvailable = true;
            cout << "? Book \"" << title << "\" returned successfully!" << endl;
        } else {
            cout << "? Book \"" << title << "\" was not borrowed!" << endl;
        }
    }

    void displayBook() {
        cout << "?? ID: " << bookID 
             << " | Title: " << title 
             << " | Author: " << author 
             << " | Status: " << (isAvailable ? "Available" : "Borrowed") 
             << endl;
    }
};

// ============================
// 2. User Class
// ============================
class User {
private:
    int userID;
    string name;
    vector<int> borrowedBooks;  // Composition: list of borrowed book IDs

public:
    // Constructor
    User(int id, string n) {
        userID = id;
        name = n;
    }

    // Getters
    int getID() { return userID; }
    string getName() { return name; }

    // Borrow a book (add to borrowed list)
    void borrowBook(int bookID) {
        borrowedBooks.push_back(bookID);
        cout << "?? User \"" << name << "\" borrowed book ID: " << bookID << endl;
    }

    // Return a book (remove from borrowed list)
    void returnBook(int bookID) {
        for (int i = 0; i < borrowedBooks.size(); i++) {
            if (borrowedBooks[i] == bookID) {
                borrowedBooks.erase(borrowedBooks.begin() + i);
                cout << "?? User \"" << name << "\" returned book ID: " << bookID << endl;
                return;
            }
        }
        cout << "? User \"" << name << "\" did not borrow this book!" << endl;
    }

    // Display borrowed books
    void displayBorrowedBooks() {
        cout << "?? Books borrowed by " << name << ": ";
        if (borrowedBooks.empty()) {
            cout << "None" << endl;
        } else {
            for (int id : borrowedBooks) {
                cout << id << " ";
            }
            cout << endl;
        }
    }
};

// ============================
// 3. Library Class (Composition)
// ============================
class Library {
private:
    vector<Book> books;     // Composition: Library has many Books
    vector<User> users;     // Composition: Library has many Users

public:
    // Add a new book
    void addBook(int id, string title, string author) {
        Book newBook(id, title, author);
        books.push_back(newBook);
        cout << "? Book added successfully!" << endl;
    }

    // Add a new user
    void addUser(int id, string name) {
        User newUser(id, name);
        users.push_back(newUser);
        cout << "? User added successfully!" << endl;
    }

    // Find book by ID
    Book* findBook(int id) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getID() == id) {
                return &books[i];
            }
        }
        return nullptr;
    }

    // Find user by ID
    User* findUser(int id) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].getID() == id) {
                return &users[i];
            }
        }
        return nullptr;
    }

    // Borrow a book
    void borrowBook(int userID, int bookID) {
        Book* book = findBook(bookID);
        User* user = findUser(userID);

        if (book == nullptr) {
            cout << "? Book not found!" << endl;
            return;
        }
        if (user == nullptr) {
            cout << "? User not found!" << endl;
            return;
        }

        if (book->getAvailability()) {
            book->borrowBook();
            user->borrowBook(bookID);
        } else {
            cout << "? Book is already borrowed!" << endl;
        }
    }

    // Return a book
    void returnBook(int userID, int bookID) {
        Book* book = findBook(bookID);
        User* user = findUser(userID);

        if (book == nullptr) {
            cout << "? Book not found!" << endl;
            return;
        }
        if (user == nullptr) {
            cout << "? User not found!" << endl;
            return;
        }

        book->returnBook();
        user->returnBook(bookID);
    }

    // Display all books
    void displayAllBooks() {
        if (books.empty()) {
            cout << "?? No books in library!" << endl;
            return;
        }
        cout << "\n?? ===== All Books ===== ??" << endl;
        for (int i = 0; i < books.size(); i++) {
            books[i].displayBook();
        }
    }

    // Display all users
    void displayAllUsers() {
        if (users.empty()) {
            cout << "?? No users registered!" << endl;
            return;
        }
        cout << "\n?? ===== All Users ===== ??" << endl;
        for (int i = 0; i < users.size(); i++) {
            cout << "ID: " << users[i].getID() 
                 << " | Name: " << users[i].getName() << endl;
        }
    }
};

// ============================
// 4. Main Function (Menu)
// ============================
int main() {
    Library lib;
    int choice;

    do {
        cout << "\n========================================" << endl;
        cout << "?? LIBRARY MANAGEMENT SYSTEM ??" << endl;
        cout << "========================================" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Add User" << endl;
        cout << "3. Display All Books" << endl;
        cout << "4. Display All Users" << endl;
        cout << "5. Borrow Book" << endl;
        cout << "6. Return Book" << endl;
        cout << "7. Exit" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string title, author;
                cout << "Enter Book ID: ";
                cin >> id;
                cout << "Enter Book Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                lib.addBook(id, title, author);
                break;
            }
            case 2: {
                int id;
                string name;
                cout << "Enter User ID: ";
                cin >> id;
                cout << "Enter User Name: ";
                cin.ignore();
                getline(cin, name);
                lib.addUser(id, name);
                break;
            }
            case 3:
                lib.displayAllBooks();
                break;
            case 4:
                lib.displayAllUsers();
                break;
            case 5: {
                int userID, bookID;
                cout << "Enter User ID: ";
                cin >> userID;
                cout << "Enter Book ID: ";
                cin >> bookID;
                lib.borrowBook(userID, bookID);
                break;
            }
            case 6: {
                int userID, bookID;
                cout << "Enter User ID: ";
                cin >> userID;
                cout << "Enter Book ID: ";
                cin >> bookID;
                lib.returnBook(userID, bookID);
                break;
            }
            case 7:
                cout << "?? Exiting... Thank you!" << endl;
                break;
            default:
                cout << "? Invalid choice! Try again." << endl;
        }
    } while (choice != 7);

    return 0;
}