/*
LEVEL     : Advanced - capstone mini project
TOPIC     : Library Management System
YOU LEARN : how all earlier lessons fit together in one small program:
            - classes, encapsulation, constructors, const-correctness
            - composition (Library owns Books and Members)
            - operator<< overloading
            - a custom exception type
            - STL containers (map, vector) and <algorithm>
            - a scripted scenario in main() so it runs without typing input

NOTE: needs C++17.

EXERCISE IDEAS (extend the project!)
  1. Add a due date and a late fee.
  2. Save and load the library from a file (see 08_file_handling.cpp).
  3. Make an abstract class Item with Book and Magazine as children.
  4. Add search by author using std::find_if and a lambda.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------
// Custom exception for every business-rule failure
// ---------------------------------------------------------------------------
class LibraryError : public runtime_error
{
public:
    explicit LibraryError(const string& msg) : runtime_error(msg) {}
};

// ---------------------------------------------------------------------------
// Book
// ---------------------------------------------------------------------------
class Book
{
private:
    int id;
    string title;
    string author;
    bool available;

public:
    Book(int i, const string& t, const string& a)
        : id(i), title(t), author(a), available(true) {}

    int getId() const { return id; }
    const string& getTitle() const { return title; }
    bool isAvailable() const { return available; }
    void setAvailable(bool value) { available = value; }

    friend ostream& operator<<(ostream& out, const Book& b)
    {
        out << "#" << b.id << " \"" << b.title << "\" by " << b.author
            << (b.available ? " [available]" : " [issued]");
        return out;
    }
};

// ---------------------------------------------------------------------------
// Member
// ---------------------------------------------------------------------------
class Member
{
private:
    int id;
    string name;
    vector<int> borrowed;           // ids of books currently held

public:
    static constexpr size_t MAX_BOOKS = 2;

    Member(int i, const string& n) : id(i), name(n) {}

    int getId() const { return id; }
    const string& getName() const { return name; }
    size_t borrowedCount() const { return borrowed.size(); }
    const vector<int>& getBorrowed() const { return borrowed; }

    void addBook(int bookId) { borrowed.push_back(bookId); }

    bool removeBook(int bookId)
    {
        auto it = find(borrowed.begin(), borrowed.end(), bookId);
        if (it == borrowed.end())
            return false;
        borrowed.erase(it);
        return true;
    }
};

// ---------------------------------------------------------------------------
// Library: composes Books and Members and enforces the rules
// ---------------------------------------------------------------------------
class Library
{
private:
    map<int, Book> books;
    map<int, Member> members;

    Book& findBook(int bookId)
    {
        auto it = books.find(bookId);
        if (it == books.end())
            throw LibraryError("No book with id " + to_string(bookId));
        return it->second;
    }

    Member& findMember(int memberId)
    {
        auto it = members.find(memberId);
        if (it == members.end())
            throw LibraryError("No member with id " + to_string(memberId));
        return it->second;
    }

public:
    void addBook(const Book& b)
    {
        if (books.count(b.getId()))
            throw LibraryError("Duplicate book id " + to_string(b.getId()));
        books.insert({b.getId(), b});
    }

    void addMember(const Member& m)
    {
        if (members.count(m.getId()))
            throw LibraryError("Duplicate member id " + to_string(m.getId()));
        members.insert({m.getId(), m});
    }

    void borrowBook(int memberId, int bookId)
    {
        Member& member = findMember(memberId);
        Book& book = findBook(bookId);

        if (!book.isAvailable())
            throw LibraryError("\"" + book.getTitle() + "\" is already issued");
        if (member.borrowedCount() >= Member::MAX_BOOKS)
            throw LibraryError(member.getName() + " already holds the maximum of " +
                               to_string(Member::MAX_BOOKS) + " books");

        book.setAvailable(false);
        member.addBook(bookId);
    }

    void returnBook(int memberId, int bookId)
    {
        Member& member = findMember(memberId);
        Book& book = findBook(bookId);

        if (!member.removeBook(bookId))
            throw LibraryError(member.getName() + " did not borrow \"" + book.getTitle() + "\"");

        book.setAvailable(true);
    }

    void report() const
    {
        cout << "\n----- Library report -----" << endl;
        cout << "Books:" << endl;
        for (const auto& [id, book] : books)
            cout << "  " << book << endl;

        cout << "Members:" << endl;
        for (const auto& [id, member] : members)
        {
            cout << "  " << member.getName() << " holds " << member.borrowedCount() << " book(s)";
            for (int bookId : member.getBorrowed())
                cout << " [#" << bookId << "]";
            cout << endl;
        }
    }
};

int main()
{
    Library lib;

    lib.addBook(Book(1, "The C++ Programming Language", "Bjarne Stroustrup"));
    lib.addBook(Book(2, "Effective Modern C++", "Scott Meyers"));
    lib.addBook(Book(3, "Clean Code", "Robert C. Martin"));

    lib.addMember(Member(100, "Aman"));
    lib.addMember(Member(101, "Riya"));

    // Runs one action and reports success or the reason for failure
    auto attempt = [](const string& label, auto action) {
        cout << label << ": ";
        try
        {
            action();
            cout << "OK" << endl;
        }
        catch (const LibraryError& e)
        {
            cout << "FAILED - " << e.what() << endl;
        }
    };

    attempt("Aman borrows book 1", [&] { lib.borrowBook(100, 1); });
    attempt("Riya borrows book 1 (taken)", [&] { lib.borrowBook(101, 1); });
    attempt("Aman borrows book 2", [&] { lib.borrowBook(100, 2); });
    attempt("Aman borrows book 3 (limit)", [&] { lib.borrowBook(100, 3); });
    attempt("Riya borrows unknown book 99", [&] { lib.borrowBook(101, 99); });
    attempt("Riya returns book 1 (not hers)", [&] { lib.returnBook(101, 1); });
    attempt("Aman returns book 1", [&] { lib.returnBook(100, 1); });
    attempt("Riya borrows book 1 (now free)", [&] { lib.borrowBook(101, 1); });

    lib.report();
    return 0;
}
