/*
Design Rect class with:

data members: length and breadth

member functions:
setLength()
setBreadth()
area()
perimeter()
show()

Requirements of main() function:
Show area of a rectangle.
Create  2 Rectangle objects in main()
Use setter methods
Show (print) area and perimeter of all rectangle
Make 2 constructors - default and parameterised
Make one object each using these constructors
Show the objects*/



#include <iostream>
using namespace std;

class Rect
{
private:
    float length;
    float breadth;

public:
    // Default constructor
    Rect()
    {
        length = 0;
        breadth = 0;
    }

    // Parameterized constructor
    Rect(float l, float b)
    {
        length = l;
        breadth = b;
    }

    // Setter for length
    void setLength(float l)
    {
        length = l;
    }

    // Setter for breadth
    void setBreadth(float b)
    {
        breadth = b;
    }

    // Calculate area
    float area() const
    {
        return length * breadth;
    }

    // Calculate perimeter
    float perimeter() const
    {
        return 2 * (length + breadth);
    }

    // Display rectangle details
    void show() const
    {
        cout << "Length    : " << length << endl;
        cout << "Breadth   : " << breadth << endl;
        cout << "Area      : " << area() << endl;
        cout << "Perimeter : " << perimeter() << endl;
    }
};

int main()
{
    // Rectangle object using default constructor
    Rect r1;

    // Using setter methods
    r1.setLength(10);
    r1.setBreadth(5);

    // Rectangle object using parameterized constructor
    Rect r2(8, 4);

    cout << "Rectangle 1 (Default Constructor + Setters)" << endl;
    r1.show();

    cout << "\nRectangle 2 (Parameterized Constructor)" << endl;
    r2.show();

    return 0;
}