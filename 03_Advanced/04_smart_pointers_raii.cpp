/*
LEVEL     : Advanced
TOPIC     : Smart Pointers and RAII
YOU LEARN : - RAII: tie a resource's lifetime to an object's lifetime
            - std::unique_ptr  (single owner)
            - std::shared_ptr  (shared ownership, reference counted)
            - std::weak_ptr    (non-owning observer, breaks cycles)
            - make_unique / make_shared
            - polymorphism with smart pointers

IDEA
Raw `new` / `delete` is easy to get wrong (leaks, double delete, exceptions
skipping the delete). Smart pointers delete automatically, so modern C++
code almost never writes `delete`.

NOTE: needs C++14 or later.

EXERCISE : Create two shared_ptr<Node> that point to each other using weak_ptr
           for the back link, and confirm both destructors run.
*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Resource
{
    string name;

public:
    explicit Resource(const string& n) : name(n)
    {
        cout << "  + Resource " << name << " created" << endl;
    }
    ~Resource() { cout << "  - Resource " << name << " destroyed" << endl; }

    void use() const { cout << "  using " << name << endl; }
};

// Polymorphism through unique_ptr
class Animal
{
public:
    virtual ~Animal() {}
    virtual void speak() const = 0;
};

class Dog : public Animal
{
public:
    void speak() const override { cout << "  Woof" << endl; }
};

class Cat : public Animal
{
public:
    void speak() const override { cout << "  Meow" << endl; }
};

// Cycle demo: two objects pointing at each other with shared_ptr would leak.
struct Child;

struct Parent
{
    shared_ptr<Child> child;
    ~Parent() { cout << "  - Parent destroyed" << endl; }
};

struct Child
{
    weak_ptr<Parent> parent;      // weak: does NOT keep the parent alive
    ~Child() { cout << "  - Child destroyed" << endl; }
};

int main()
{
    cout << "=== unique_ptr: exactly one owner ===" << endl;
    {
        unique_ptr<Resource> r1 = make_unique<Resource>("A");
        r1->use();

        // unique_ptr<Resource> r2 = r1;     // ERROR: cannot copy
        unique_ptr<Resource> r2 = std::move(r1);   // ownership transferred
        cout << "  r1 is " << (r1 ? "valid" : "empty") << " after move" << endl;
        r2->use();
    }   // r2 goes out of scope -> Resource A destroyed automatically

    cout << "\n=== shared_ptr: shared ownership ===" << endl;
    {
        shared_ptr<Resource> s1 = make_shared<Resource>("B");
        cout << "  use_count = " << s1.use_count() << endl;
        {
            shared_ptr<Resource> s2 = s1;       // copy -> count goes up
            cout << "  use_count = " << s1.use_count() << endl;
        }
        cout << "  use_count = " << s1.use_count() << " (s2 gone)" << endl;
    }   // last owner gone -> destroyed

    cout << "\n=== weak_ptr: observe without owning ===" << endl;
    {
        weak_ptr<Resource> weak;
        {
            shared_ptr<Resource> strong = make_shared<Resource>("C");
            weak = strong;
            if (auto locked = weak.lock())      // try to get a temporary owner
                cout << "  still alive, using it" << endl;
        }
        cout << "  expired? " << (weak.expired() ? "yes" : "no") << endl;
    }

    cout << "\n=== Breaking a parent <-> child cycle ===" << endl;
    {
        auto parent = make_shared<Parent>();
        parent->child = make_shared<Child>();
        parent->child->parent = parent;         // weak back-pointer
    }   // both destroyed (with shared_ptr on both sides they would LEAK)

    cout << "\n=== Polymorphism with unique_ptr ===" << endl;
    vector<unique_ptr<Animal>> zoo;
    zoo.push_back(make_unique<Dog>());
    zoo.push_back(make_unique<Cat>());
    for (const auto& a : zoo)
        a->speak();
    // no delete needed: the vector frees everything

    return 0;
}
