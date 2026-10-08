/*
LEVEL     : Intermediate
TOPIC     : Friends, Composition and Aggregation
YOU LEARN : - friend function and friend class
            - "has-a" relationships: composition vs aggregation
            - when to prefer composition over inheritance

IDEA
* Inheritance  = "is-a"   (Dog is an Animal)
* Composition  = "has-a", the part DIES with the whole (Car has an Engine)
* Aggregation  = "has-a", the part can LIVE ON its own (Department has Teachers)

Prefer composition over inheritance unless the "is-a" relation is really true.

See also: IPU/friend.cpp for a friend function of two classes.

EXERCISE : Add a method to Department that finds the teacher with the most
           experience.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------
// Friend class
// ---------------------------------------------------------------------------
class Vault
{
private:
    int secretCode = 4821;
    friend class Auditor;               // Auditor may see Vault's private data
    friend void resetCode(Vault&);      // so may this free function
};

class Auditor
{
public:
    void inspect(const Vault& v) const
    {
        cout << "Auditor sees secret code: " << v.secretCode << endl;
    }
};

void resetCode(Vault& v)
{
    v.secretCode = 0;
    cout << "Code reset by friend function." << endl;
}

// ---------------------------------------------------------------------------
// Composition: Engine is created and destroyed together with Car
// ---------------------------------------------------------------------------
class Engine
{
    int horsepower;

public:
    explicit Engine(int hp) : horsepower(hp)
    {
        cout << "  Engine(" << horsepower << " hp) built" << endl;
    }
    ~Engine() { cout << "  Engine destroyed" << endl; }

    void start() const { cout << "  Engine with " << horsepower << " hp starts" << endl; }
};

class Car
{
    string model;
    Engine engine;                      // the Car OWNS the engine (a member object)

public:
    Car(const string& m, int hp) : model(m), engine(hp)
    {
        cout << "  Car " << model << " built" << endl;
    }
    ~Car() { cout << "  Car " << model << " destroyed" << endl; }

    void drive() const
    {
        cout << model << ": ";
        engine.start();
    }
};

// ---------------------------------------------------------------------------
// Aggregation: Department only REFERS to teachers that exist elsewhere
// ---------------------------------------------------------------------------
class Teacher
{
public:
    string name;
    explicit Teacher(const string& n) : name(n) {}
};

class Department
{
    string title;
    vector<const Teacher*> staff;       // non-owning pointers

public:
    explicit Department(const string& t) : title(t) {}

    void addTeacher(const Teacher* t) { staff.push_back(t); }

    void list() const
    {
        cout << "Department of " << title << ":" << endl;
        for (const Teacher* t : staff)
            cout << "  - " << t->name << endl;
    }
};

int main()
{
    cout << "=== Friends ===" << endl;
    Vault vault;
    Auditor auditor;
    auditor.inspect(vault);
    resetCode(vault);
    auditor.inspect(vault);

    cout << "\n=== Composition ===" << endl;
    {
        Car car("Swift", 90);
        car.drive();
    }   // Engine goes away with the Car

    cout << "\n=== Aggregation ===" << endl;
    Teacher t1("Dr. Rao"), t2("Prof. Iyer");
    {
        Department cs("Computer Science");
        cs.addTeacher(&t1);
        cs.addTeacher(&t2);
        cs.list();
    }   // Department is gone, but the teachers still exist
    cout << t1.name << " and " << t2.name << " are still alive." << endl;

    return 0;
}
