/*
LEVEL     : Intermediate
TOPIC     : Polymorphism (compile-time and run-time)
YOU LEARN : - function overloading (compile-time polymorphism)
            - virtual functions and override (run-time polymorphism)
            - base-class pointers to derived objects
            - virtual destructors
            - object slicing (a classic bug)
            - `final`

IDEA
Polymorphism = "many forms". With a base-class pointer, calling a VIRTUAL
function runs the version belonging to the REAL object, decided at run time.
Without `virtual`, the version of the pointer's type is used.

EXERCISE : Add a Triangle class (base, height) and put one in the array.
*/

#include <iostream>
using namespace std;

const double PI = 3.14159265358979;

// ---------------------------------------------------------------------------
// 1. Compile-time polymorphism: same name, different parameters
// ---------------------------------------------------------------------------
class Printer
{
public:
    void print(int x) const { cout << "int: " << x << endl; }
    void print(double x) const { cout << "double: " << x << endl; }
    void print(const char* s) const { cout << "text: " << s << endl; }
};

// ---------------------------------------------------------------------------
// 2. Run-time polymorphism
// ---------------------------------------------------------------------------
class Shape
{
public:
    virtual ~Shape() { cout << "  ~Shape" << endl; }   // ALWAYS virtual in a base

    virtual double area() const { return 0; }
    virtual const char* name() const { return "Shape"; }

    // Non-virtual: decided by pointer type, NOT by real object
    const char* nonVirtualName() const { return "Shape (non-virtual)"; }
};

class Circle : public Shape
{
    double r;

public:
    explicit Circle(double radius) : r(radius) {}
    ~Circle() override { cout << "  ~Circle" << endl; }

    // `override` makes the compiler check we really override a virtual function
    double area() const override { return PI * r * r; }
    const char* name() const override { return "Circle"; }
    const char* nonVirtualName() const { return "Circle (non-virtual)"; }
};

class Rectangle : public Shape
{
    double w, h;

public:
    Rectangle(double width, double height) : w(width), h(height) {}
    ~Rectangle() override { cout << "  ~Rectangle" << endl; }

    double area() const override { return w * h; }
    const char* name() const override { return "Rectangle"; }
};

// `final` stops anyone from overriding / inheriting further
class Square final : public Rectangle
{
public:
    explicit Square(double side) : Rectangle(side, side) {}
    const char* name() const override { return "Square"; }
};

// Takes the base BY VALUE -> SLICING: only the Shape part is copied
double areaByValue(Shape s)
{
    return s.area();
}

int main()
{
    cout << "=== Overloading (compile-time) ===" << endl;
    Printer p;
    p.print(5);
    p.print(2.5);
    p.print("hello");

    cout << "\n=== Virtual functions (run-time) ===" << endl;
    Shape* shapes[3];
    shapes[0] = new Circle(2);
    shapes[1] = new Rectangle(3, 4);
    shapes[2] = new Square(5);

    for (int i = 0; i < 3; i++)
    {
        // Same call, different behaviour depending on the real object
        cout << shapes[i]->name() << " area = " << shapes[i]->area() << endl;
    }

    cout << "\nNon-virtual function uses the POINTER type:" << endl;
    cout << shapes[0]->nonVirtualName() << endl;       // prints Shape's version

    cout << "\n=== Object slicing ===" << endl;
    Circle c(2);
    cout << "Circle area via reference/pointer: " << c.area() << endl;
    cout << "Circle area after passing BY VALUE as Shape: " << areaByValue(c)
         << "  <- sliced, now just a Shape!" << endl;
    cout << "Rule: pass polymorphic objects by pointer or reference." << endl;

    cout << "\n=== Cleanup (virtual destructor makes this correct) ===" << endl;
    for (int i = 0; i < 3; i++)
    {
        delete shapes[i];       // runs ~Derived then ~Shape because ~Shape is virtual
        cout << "  ----" << endl;
    }

    return 0;
}
