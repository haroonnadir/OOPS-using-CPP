/*
Title: Constructor Overloading (Complex Numbers)
Problem Statement:
Implement constructor
overloading in a Complex class and perform addition of complex numbers.

- Your solution should define a class for Complex that defines state
attributes of the class, constructor for the class and show() and add()
 methods on the class.

- The add method which takes an object of type Complex as input and returns
an object of type Complex that stores the result of addition of two Complex
objects.

- The show method prints the complex object in the form (<real part>
+ <img part) i>
*/


#include <iostream>
using namespace std;

class Complex
{
private:
    float real;
    float img;

public:
    // Default constructor
    Complex()
    {
        real = 0;
        img = 0;
    }

    // Parameterized constructor
    Complex(float r, float i)
    {
        real = r;
        img = i;
    }

    // Add two complex numbers
    Complex add(const Complex& c) const
    {
        Complex result;
        result.real = real + c.real;
        result.img = img + c.img;
        return result;
    }

    // Display complex number
    void show() const
    {
        cout << "(" << real << " + " << img << "i)" << endl;
    }
};

int main()
{
    Complex c1(3, 4);
    Complex c2(5, 6);

    cout << "First Complex Number: ";
    c1.show();

    cout << "Second Complex Number: ";
    c2.show();

    Complex c3 = c1.add(c2);

    cout << "Addition: ";
    c3.show();

    return 0;
}