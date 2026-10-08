/*
LEVEL     : Intermediate
TOPIC     : Shallow copy vs Deep copy, and the Rule of Three
YOU LEARN : - what goes wrong when a class owns raw memory
            - writing destructor + copy constructor + copy assignment
            - the self-assignment check

IDEA
If a class holds a raw pointer (int* data), the compiler-generated copy just
copies the ADDRESS (shallow copy). Two objects now share one array. When both
are destroyed, the same memory is freed twice -> crash.

RULE OF THREE: if you write ANY of
    destructor, copy constructor, copy assignment operator
you almost certainly need ALL THREE.

See also: IPU/matrix_multiplication.cpp (same idea for a 2D array).

EXERCISE : Add a method resize(int newSize) that keeps the old values.
*/

#include <iostream>
using namespace std;

class IntArray
{
private:
    int* data;
    int size;

public:
    // Constructor: owns a heap array
    explicit IntArray(int n) : data(new int[n]()), size(n)   // () zero-initializes
    {
    }

    // 1. Destructor
    ~IntArray()
    {
        delete[] data;
    }

    // 2. Copy constructor: allocate NEW memory and copy the values (deep copy)
    IntArray(const IntArray& other) : data(new int[other.size]), size(other.size)
    {
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
        cout << "  (deep copy constructor)" << endl;
    }

    // 3. Copy assignment: clean up the old memory first, then deep copy
    IntArray& operator=(const IntArray& other)
    {
        cout << "  (copy assignment)" << endl;
        if (this == &other)         // guard: a = a must not delete our own data
            return *this;

        int* newData = new int[other.size];     // allocate first: if new throws,
        for (int i = 0; i < other.size; i++)    // our old data is still intact
            newData[i] = other.data[i];

        delete[] data;
        data = newData;
        size = other.size;
        return *this;
    }

    int& at(int i) { return data[i]; }
    int at(int i) const { return data[i]; }
    int length() const { return size; }

    void print(const char* label) const
    {
        cout << label << ": ";
        for (int i = 0; i < size; i++)
            cout << data[i] << " ";
        cout << endl;
    }
};

int main()
{
    IntArray a(3);
    a.at(0) = 1;
    a.at(1) = 2;
    a.at(2) = 3;
    a.print("a");

    cout << "Copy construct b from a:" << endl;
    IntArray b = a;                 // deep copy: b has its OWN memory
    b.at(0) = 100;                  // changing b must NOT change a
    a.print("a (unchanged)");
    b.print("b");

    cout << "Assign c = a:" << endl;
    IntArray c(1);
    c = a;
    c.at(2) = 300;
    a.print("a (unchanged)");
    c.print("c");

    cout << "Self assignment is safe:" << endl;
    c = c;
    c.print("c");

    /*
    WHAT IF we had NOT written the copy constructor?
        IntArray b = a;   // copies only the pointer: a.data == b.data
    At the end of main both destructors run delete[] on the SAME address
    -> double free -> crash / undefined behaviour.
    */
    return 0;
}
