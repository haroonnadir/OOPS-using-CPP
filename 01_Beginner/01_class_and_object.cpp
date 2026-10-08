/*
LEVEL     : Beginner
TOPIC     : Class and Object
YOU LEARN : - what a class is (blueprint) and what an object is (real thing)
            - data members and member functions
            - creating single objects, arrays of objects, and pointers to objects
            - the dot (.) and arrow (->) operators

IDEA
A class is a blueprint, e.g. "Student". An object is one actual student made
from that blueprint. One class can make many objects; each has its own data.

TRY IT   : g++ -std=c++17 01_class_and_object.cpp -o class_and_object
EXERCISE : Add a member function grade() that returns 'A' for marks >= 90,
           'B' for >= 75, 'C' for >= 40 and 'F' otherwise.
*/

#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
    // Data members (the "state" of an object)
    string name;
    int rollNo;
    float marks;

    // Member functions (the "behaviour" of an object)
    void display()
    {
        cout << "Roll " << rollNo << " | " << name << " | marks: " << marks << endl;
    }

    bool isPass()
    {
        return marks >= 40;
    }
};

int main()
{
    // 1. Create an object and fill its members with the dot operator
    Student s1;
    s1.name = "Aman";
    s1.rollNo = 1;
    s1.marks = 78.5f;

    cout << "--- Single object ---" << endl;
    s1.display();
    cout << (s1.isPass() ? "Result: Pass" : "Result: Fail") << endl;

    // 2. Each object has its OWN copy of the data
    Student s2;
    s2.name = "Riya";
    s2.rollNo = 2;
    s2.marks = 35;

    cout << "\n--- Two independent objects ---" << endl;
    s1.display();
    s2.display();
    cout << "Riya: " << (s2.isPass() ? "Pass" : "Fail") << endl;

    // 3. Array of objects
    Student batch[3];
    string names[3] = {"Kabir", "Sara", "Neha"};
    for (int i = 0; i < 3; i++)
    {
        batch[i].name = names[i];
        batch[i].rollNo = 10 + i;
        batch[i].marks = 50.0f + 10 * i;
    }

    cout << "\n--- Array of objects ---" << endl;
    for (int i = 0; i < 3; i++)
        batch[i].display();

    // 4. Pointer to an object: use -> instead of .
    Student* p = &s1;
    cout << "\n--- Pointer to object ---" << endl;
    cout << "Through pointer: " << p->name << " (same as (*p).name)" << endl;

    // 5. Object created on the heap with new must be released with delete
    Student* heapStudent = new Student;
    heapStudent->name = "Heap Hero";
    heapStudent->rollNo = 99;
    heapStudent->marks = 100;
    heapStudent->display();
    delete heapStudent;

    return 0;
}
