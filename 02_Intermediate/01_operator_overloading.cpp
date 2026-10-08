/*
LEVEL     : Intermediate
TOPIC     : Operator Overloading
YOU LEARN : - overloading + - == as member functions
            - overloading << and >> as friend (non-member) functions
            - unary minus, prefix ++ and postfix ++
            - subscript operator []
            - rules: what you can and cannot overload

IDEA
Operator overloading lets your class work with the normal operators, so
`c1 + c2` reads naturally instead of `c1.add(c2)`.

Compare with IPU/complex.cpp, which uses a named add() method.

CANNOT be overloaded:  ::  .  .*  ?:  sizeof
RULE OF THUMB: overload an operator only if the meaning is obvious.

EXERCISE : Add operator* (multiply two complex numbers):
           (a+bi)(c+di) = (ac-bd) + (ad+bc)i
*/

#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

class Complex
{
private:
    double real, img;

public:
    Complex(double r = 0, double i = 0) : real(r), img(i) {}

    // Binary + as a member: left operand is *this
    Complex operator+(const Complex& rhs) const
    {
        return Complex(real + rhs.real, img + rhs.img);
    }

    Complex operator-(const Complex& rhs) const
    {
        return Complex(real - rhs.real, img - rhs.img);
    }

    // Unary minus: -c
    Complex operator-() const
    {
        return Complex(-real, -img);
    }

    bool operator==(const Complex& rhs) const
    {
        return real == rhs.real && img == rhs.img;
    }

    bool operator!=(const Complex& rhs) const
    {
        return !(*this == rhs);       // reuse ==
    }

    // << and >> need the stream on the LEFT, so they cannot be members.
    // They are made friends so they can read/write private data.
    friend ostream& operator<<(ostream& out, const Complex& c);
    friend istream& operator>>(istream& in, Complex& c);
};

ostream& operator<<(ostream& out, const Complex& c)
{
    out << "(" << c.real << (c.img < 0 ? " - " : " + ")
        << (c.img < 0 ? -c.img : c.img) << "i)";
    return out;                       // returning the stream allows chaining
}

istream& operator>>(istream& in, Complex& c)
{
    in >> c.real >> c.img;
    return in;
}

// ---------------------------------------------------------------------------
// Prefix and postfix ++
// ---------------------------------------------------------------------------
class Counter
{
private:
    int value;

public:
    Counter(int v = 0) : value(v) {}

    // Prefix ++c : increment first, return the NEW value (by reference)
    Counter& operator++()
    {
        ++value;
        return *this;
    }

    // Postfix c++ : the dummy `int` parameter tells the compiler it is postfix.
    // Return the OLD value (a copy), then increment.
    Counter operator++(int)
    {
        Counter old = *this;
        ++value;
        return old;
    }

    int get() const { return value; }
};

// ---------------------------------------------------------------------------
// Subscript operator []
// ---------------------------------------------------------------------------
class SafeArray
{
private:
    int data[5];

public:
    SafeArray()
    {
        for (int i = 0; i < 5; i++)
            data[i] = 0;
    }

    // Non-const version: allows  arr[2] = 10;
    int& operator[](int index)
    {
        if (index < 0 || index >= 5)
            throw out_of_range("SafeArray index out of range");
        return data[index];
    }

    // Const version: allows reading from a const SafeArray
    const int& operator[](int index) const
    {
        if (index < 0 || index >= 5)
            throw out_of_range("SafeArray index out of range");
        return data[index];
    }
};

int main()
{
    Complex a(3, 4), b(5, -6);

    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "-a    = " << -a << endl;
    cout << "a == b ? " << (a == b ? "yes" : "no") << endl;
    cout << "a == Complex(3,4) ? " << (a == Complex(3, 4) ? "yes" : "no") << endl;

    // operator>> demo without waiting for the keyboard: read from a string
    istringstream fakeInput("7 8");
    Complex c;
    fakeInput >> c;
    cout << "Read from stream: " << c << endl;

    cout << "\n--- ++ operators ---" << endl;
    Counter k(5);
    Counter x = k++;                  // x gets the OLD value
    cout << "after  x = k++ : x=" << x.get() << ", k=" << k.get() << endl;
    Counter y = ++k;                  // y gets the NEW value
    cout << "after  y = ++k : y=" << y.get() << ", k=" << k.get() << endl;

    cout << "\n--- [] operator ---" << endl;
    SafeArray arr;
    arr[2] = 42;
    cout << "arr[2] = " << arr[2] << endl;
    try
    {
        arr[10] = 1;
    }
    catch (const out_of_range& e)
    {
        cout << "Caught: " << e.what() << endl;
    }

    return 0;
}
