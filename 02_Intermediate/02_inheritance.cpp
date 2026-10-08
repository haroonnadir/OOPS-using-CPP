/*
LEVEL     : Intermediate
TOPIC     : Inheritance
YOU LEARN : - "is-a" relationship: Student is a Person
            - single, multilevel and hierarchical inheritance
            - protected members
            - constructor / destructor call ORDER in inheritance
            - calling the base constructor
            - function overriding vs hiding (no virtual yet - see next lesson)
            - public / protected / private inheritance

IDEA
Inheritance lets a new class (derived) reuse and extend an existing class
(base). Derived classes get the base class's members for free.

        Person                      (base)
        /    \
   Student   Employee               (hierarchical: 2 children of one parent)
      |        |
 GradStudent  Manager               (multilevel: a chain)

EXERCISE : Add a class Intern derived from Employee with a stipend.
*/

#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:                      // visible to derived classes, hidden from outside
    string name;
    int age;

public:
    Person(const string& n, int a) : name(n), age(a)
    {
        cout << "  Person ctor: " << name << endl;
    }

    ~Person()
    {
        cout << "  Person dtor: " << name << endl;
    }

    void introduce() const
    {
        cout << "Hi, I am " << name << ", age " << age << "." << endl;
    }
};

class Student : public Person
{
protected:
    int rollNo;

public:
    // Base class part is built FIRST via the initializer list
    Student(const string& n, int a, int roll) : Person(n, a), rollNo(roll)
    {
        cout << "  Student ctor: " << name << endl;
    }

    ~Student()
    {
        cout << "  Student dtor: " << name << endl;
    }

    // Same name as base -> HIDES Person::introduce (not virtual!)
    void introduce() const
    {
        Person::introduce();    // can still call the base version explicitly
        cout << "I am a student, roll number " << rollNo << "." << endl;
    }
};

// Multilevel: GradStudent -> Student -> Person
class GradStudent : public Student
{
private:
    string thesisTopic;

public:
    GradStudent(const string& n, int a, int roll, const string& topic)
        : Student(n, a, roll), thesisTopic(topic)
    {
        cout << "  GradStudent ctor: " << name << endl;
    }

    ~GradStudent()
    {
        cout << "  GradStudent dtor: " << name << endl;
    }

    void showThesis() const
    {
        cout << name << " is researching: " << thesisTopic << endl;
    }
};

// Hierarchical: Employee is another child of Person
class Employee : public Person
{
protected:
    double salary;

public:
    Employee(const string& n, int a, double s) : Person(n, a), salary(s) {}

    void showSalary() const
    {
        cout << name << " earns " << salary << endl;
    }
};

class Manager : public Employee
{
private:
    int teamSize;

public:
    Manager(const string& n, int a, double s, int team)
        : Employee(n, a, s), teamSize(team) {}

    void showTeam() const
    {
        cout << name << " manages " << teamSize << " people." << endl;
    }
};

int main()
{
    cout << "=== Creating a GradStudent (watch the order) ===" << endl;
    {
        GradStudent g("Meera", 24, 501, "Quantum Computing");
        cout << "--- using it ---" << endl;
        g.introduce();          // Student::introduce (hides Person's)
        g.showThesis();
        g.Person::introduce();  // explicitly choose the base version
        cout << "--- leaving scope (destructors run in REVERSE order) ---" << endl;
    }

    cout << "\n=== Hierarchical: Manager ===" << endl;
    Manager m("Rohan", 40, 120000, 8);
    m.introduce();              // inherited from Person
    m.showSalary();             // inherited from Employee
    m.showTeam();               // own method

    /*
    INHERITANCE MODES  (what happens to the base class's public members)
      class D : public B      -> stay public     (the normal "is-a" case)
      class D : protected B   -> become protected
      class D : private B     -> become private  ("implemented-in-terms-of")
    Private members of the base are NEVER accessible in the derived class.

    NOTE: Person has a NON-virtual destructor here, which is fine as long as we
    never `delete` a derived object through a Person*. The next lesson explains
    why polymorphic base classes must have a virtual destructor.
    */
    return 0;
}
