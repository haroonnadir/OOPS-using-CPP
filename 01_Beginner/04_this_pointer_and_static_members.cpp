/*
LEVEL     : Beginner
TOPIC     : `this` pointer and static members
YOU LEARN : - what `this` is and when you need it
            - method chaining (returning *this)
            - static data members (shared by ALL objects)
            - static member functions (called without an object)

IDEA
* Every non-static member function secretly receives a pointer to the object
  it was called on. That pointer is called `this`.
* A static member does not belong to any single object; it belongs to the
  class. There is exactly one copy, shared by everybody.

EXERCISE : Add a static function resetCount() and a static member that stores
           the largest Box volume created so far.
*/

#include <iostream>
using namespace std;

class Box
{
private:
    double length, width, height;

    static int count;               // declaration: one shared counter

public:
    Box(double length = 1, double width = 1, double height = 1)
    {
        // Parameter names equal member names, so `this->` tells them apart
        this->length = length;
        this->width = width;
        this->height = height;
        count++;
    }

    ~Box() { count--; }

    // Each setter returns a reference to the SAME object, so calls can be chained:
    //   box.setLength(5).setWidth(2).setHeight(3);
    Box& setLength(double l) { length = l; return *this; }
    Box& setWidth(double w)  { width = w;  return *this; }
    Box& setHeight(double h) { height = h; return *this; }

    double volume() const { return length * width * height; }

    // Check if two objects are the same object (compare addresses)
    bool isSameObject(const Box& other) const { return this == &other; }

    // Static function: no `this`, can only touch static members
    static int getCount() { return count; }
};

// Definition (allocates the storage) must appear once, outside the class
int Box::count = 0;

int main()
{
    cout << "Boxes alive at start: " << Box::getCount() << endl;   // no object needed

    Box a(2, 3, 4);
    Box b;                       // uses default arguments -> 1 x 1 x 1
    cout << "Boxes alive after creating a and b: " << Box::getCount() << endl;

    cout << "a.volume = " << a.volume() << ", b.volume = " << b.volume() << endl;

    // Method chaining thanks to `return *this`
    b.setLength(5).setWidth(2).setHeight(3);
    cout << "b.volume after chaining = " << b.volume() << endl;

    cout << "a is a? " << (a.isSameObject(a) ? "yes" : "no") << endl;
    cout << "a is b? " << (a.isSameObject(b) ? "yes" : "no") << endl;

    {
        Box temp;
        cout << "Inside block, boxes alive: " << Box::getCount() << endl;
    }
    cout << "After block, boxes alive: " << Box::getCount() << endl;

    return 0;
}
