/*
LEVEL     : Advanced
TOPIC     : Multiple Inheritance and the Diamond Problem
YOU LEARN : - a class with more than one base class
            - ambiguity and how to resolve it with ::
            - the "diamond" and why it duplicates the base subobject
            - virtual inheritance as the fix
            - who constructs the shared virtual base

            Animal
            /    \
        Mammal   Winged
            \    /
              Bat

EXERCISE : Add a data member `int age` to Animal and print it from Bat.
           Then remove `virtual` and see the compiler complain.
*/

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------------------
// Part 1: simple ambiguity with two unrelated bases
// ---------------------------------------------------------------------------
class Camera
{
public:
    void powerOn() const { cout << "Camera on" << endl; }
};

class Phone
{
public:
    void powerOn() const { cout << "Phone on" << endl; }
};

class SmartPhone : public Camera, public Phone
{
public:
    void powerOn() const        // resolve by defining our own, calling both
    {
        Camera::powerOn();
        Phone::powerOn();
    }
};

// ---------------------------------------------------------------------------
// Part 2: the diamond WITHOUT virtual inheritance
// ---------------------------------------------------------------------------
class AnimalBad
{
public:
    string name;
    explicit AnimalBad(const string& n = "?") : name(n) {}
};

class MammalBad : public AnimalBad
{
public:
    MammalBad() : AnimalBad("mammal-part") {}
};

class WingedBad : public AnimalBad
{
public:
    WingedBad() : AnimalBad("winged-part") {}
};

class BatBad : public MammalBad, public WingedBad
{
    // Bat contains TWO AnimalBad subobjects!
};

// ---------------------------------------------------------------------------
// Part 3: the diamond WITH virtual inheritance
// ---------------------------------------------------------------------------
class Animal
{
public:
    string name;
    explicit Animal(const string& n = "?") : name(n)
    {
        cout << "  Animal(" << name << ") constructed" << endl;
    }
    virtual ~Animal() {}
};

class Mammal : virtual public Animal
{
public:
    Mammal() : Animal("from-Mammal")      // IGNORED when building a Bat
    {
        cout << "  Mammal constructed" << endl;
    }
};

class Winged : virtual public Animal
{
public:
    Winged() : Animal("from-Winged")      // IGNORED when building a Bat
    {
        cout << "  Winged constructed" << endl;
    }
};

class Bat : public Mammal, public Winged
{
public:
    // The MOST DERIVED class constructs the single shared virtual base
    Bat() : Animal("Bat"), Mammal(), Winged()
    {
        cout << "  Bat constructed" << endl;
    }
};

int main()
{
    cout << "=== Ambiguity ===" << endl;
    SmartPhone sp;
    // sp.Camera::powerOn() / sp.Phone::powerOn() also work individually
    sp.powerOn();

    cout << "\n=== Diamond without virtual ===" << endl;
    BatBad bad;
    // cout << bad.name;            // ERROR: ambiguous - which AnimalBad?
    cout << "via Mammal: " << bad.MammalBad::name << endl;
    cout << "via Winged: " << bad.WingedBad::name << endl;
    cout << "sizeof(BatBad) = " << sizeof(BatBad) << " (two copies of name)" << endl;

    cout << "\n=== Diamond with virtual inheritance ===" << endl;
    Bat bat;
    cout << "bat.name = " << bat.name << "  (one shared Animal, no ambiguity)" << endl;

    /*
    ADVICE: multiple inheritance of IMPLEMENTATION is rarely a good idea.
    Multiple inheritance of pure INTERFACES (see 02_Intermediate/04) is safe
    and common. Prefer composition when in doubt.
    */
    return 0;
}
