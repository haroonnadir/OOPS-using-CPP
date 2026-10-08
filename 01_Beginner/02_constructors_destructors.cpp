/*
LEVEL     : Beginner
TOPIC     : Constructors and Destructors
YOU LEARN : - default, parameterized and copy constructors
            - constructor overloading
            - member initializer list (the preferred way to initialize)
            - delegating constructors
            - destructor, and the ORDER in which objects are created/destroyed

IDEA
A constructor runs automatically when an object is created, so the object
always starts in a valid state. A destructor runs automatically when the
object dies (goes out of scope or is deleted) and is used to clean up.

See also: IPU/complex.cpp and PRACTICE/distance.cpp (constructor overloading).

EXERCISE : Add a constructor Book(string title) that sets pages to 100 by
           delegating to the 2-argument constructor.
*/

#include <iostream>
#include <string>
using namespace std;

class Book
{
private:
    string title;
    int pages;

public:
    // 1. Default constructor (no arguments)
    Book() : title("Untitled"), pages(0)
    {
        cout << "  [default ctor] " << title << endl;
    }

    // 2. Parameterized constructor, using a member initializer list.
    //    "title(t), pages(p)" initializes members directly (faster than
    //    assigning inside the body, and REQUIRED for const/reference members).
    Book(const string& t, int p) : title(t), pages(p)
    {
        cout << "  [param ctor]   " << title << endl;
    }

    // 3. Delegating constructor: calls another constructor of the same class
    Book(const string& t) : Book(t, 100)
    {
        cout << "  [delegating ctor] finished for " << title << endl;
    }

    // 4. Copy constructor: builds a new object from an existing one
    Book(const Book& other) : title(other.title + " (copy)"), pages(other.pages)
    {
        cout << "  [copy ctor]    " << title << endl;
    }

    // Destructor: same name with ~, no arguments, no return type
    ~Book()
    {
        cout << "  [destructor]   " << title << endl;
    }

    void show() const
    {
        cout << "  " << title << " - " << pages << " pages" << endl;
    }
};

int main()
{
    cout << "Creating b1 (default):" << endl;
    Book b1;

    cout << "Creating b2 (parameterized):" << endl;
    Book b2("C++ Primer", 976);

    cout << "Creating b3 (delegating):" << endl;
    Book b3("Notes");

    cout << "Creating b4 (copy of b2):" << endl;
    Book b4 = b2;           // also: Book b4(b2);
    b4.show();

    {
        cout << "Entering inner block..." << endl;
        Book temp("Temporary", 10);
        temp.show();
        cout << "Leaving inner block..." << endl;
    }   // temp is destroyed right here

    cout << "End of main. Remaining objects are destroyed in REVERSE order"
         << " of creation (b4, b3, b2, b1):" << endl;
    return 0;
}
