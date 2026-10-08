/*
LEVEL     : Beginner
TOPIC     : References, pointers and const (needed for all OOP code)
YOU LEARN : - pass by value vs pass by reference vs pass by const reference
            - why objects should usually be passed as `const T&`
            - const objects can only call const member functions
            - `mutable` members

IDEA
Passing an object by value COPIES it (slow, and may be wrong for objects that
own memory). Passing by reference passes the original. Adding const promises
the function will not change it.

EXERCISE : Write a function `void rename(Person& p, const string& newName)`
           and call it from main.
*/

#include <iostream>
#include <string>
using namespace std;

class Person
{
private:
    string name;
    int age;
    mutable int readCount;      // mutable: may change even inside const functions

public:
    Person(const string& n, int a) : name(n), age(a), readCount(0) {}

    // const method: promises not to change visible state of the object
    string getName() const
    {
        readCount++;            // allowed only because readCount is mutable
        return name;
    }
    int getAge() const { return age; }
    int getReadCount() const { return readCount; }

    void birthday() { age++; }  // NOT const: it changes the object
};

// By value: gets a COPY, so changes do not affect the caller
void birthdayByValue(Person p)
{
    p.birthday();
}

// By reference: works on the ORIGINAL
void birthdayByReference(Person& p)
{
    p.birthday();
}

// By const reference: no copy AND no modification allowed. Best for reading.
void printPerson(const Person& p)
{
    cout << p.getName() << " is " << p.getAge() << " years old" << endl;
    // p.birthday();        // ERROR: p is const, birthday() is not
}

int main()
{
    Person amit("Amit", 20);

    birthdayByValue(amit);
    cout << "After birthdayByValue     : ";
    printPerson(amit);                     // still 20

    birthdayByReference(amit);
    cout << "After birthdayByReference : ";
    printPerson(amit);                     // now 21

    const Person fixed("Fixed Fatima", 30);
    cout << fixed.getName() << " " << fixed.getAge() << endl;
    // fixed.birthday();    // ERROR: a const object can only call const methods

    cout << "getName() was called " << fixed.getReadCount() << " time(s) on 'fixed'" << endl;

    // Pointer vs reference
    int x = 10;
    int* ptr = &x;      // can be reseated, can be nullptr, needs *ptr to use
    int& ref = x;       // alias for x, must be initialized, cannot be reseated
    *ptr = 20;
    cout << "x=" << x << " ref=" << ref << endl;
    ref = 30;
    cout << "x=" << x << " *ptr=" << *ptr << endl;

    return 0;
}
