/*
Title: Point
Problem Statement:
Design a class Point to represent a point in 2D plane.
Private data members
x (float)
y (float)

Constructors
1. Default constructor Initialize: x = 0 y = 0
2. Constructor with one argument If only one value provided: then: x & y are set to that one value.
3. Constructor with two arguments

Member functions
show()         Display point as: (2, 7)
distanceFromOrigin()
distanceBetween()     Distance between two points

In main(): Create: Object 1 using default constructor
Object 2 using one argument constructor
Object 3 using two argument constructor
Print all.
Find distance of each point from origin.
Find distance between object 2 and object 3.

Problem Type: Practice
GitHub: Yes
Physical Lab file: No*/

#include <iostream>
#include <cmath>
using namespace std;

class Point
{
private:
    float x;
    float y;

public:
    // Default constructor
    Point()
    {
        x = 0;
        y = 0;
    }

    // Constructor with one argument
    Point(float a)
    {
        x = a;
        y = a;
    }

    // Constructor with two arguments
    Point(float a, float b)
    {
        x = a;
        y = b;
    }

    // Display point
    void show() const
    {
        cout << "(" << x << ", " << y << ")" << endl;
    }

    // Distance from origin
    float distanceFromOrigin() const
    {
        return sqrt(x * x + y * y);
    }

    // Distance between two points
    float distanceBetween(const Point& p) const
    {
        return sqrt((x - p.x) * (x - p.x) +
                    (y - p.y) * (y - p.y));
    }
};

int main()
{
    // Object 1 using default constructor
    Point p1;

    // Object 2 using one argument constructor
    Point p2(3);

    // Object 3 using two argument constructor
    Point p3(2, 7);

    cout << "Object 1: ";
    p1.show();

    cout << "Object 2: ";
    p2.show();

    cout << "Object 3: ";
    p3.show();

    cout << "\nDistance of Object 1 from origin: "
         << p1.distanceFromOrigin() << endl;

    cout << "Distance of Object 2 from origin: "
         << p2.distanceFromOrigin() << endl;

    cout << "Distance of Object 3 from origin: "
         << p3.distanceFromOrigin() << endl;

    cout << "\nDistance between Object 2 and Object 3: "
         << p2.distanceBetween(p3) << endl;

    return 0;
}