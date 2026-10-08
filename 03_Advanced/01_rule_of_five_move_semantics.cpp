/*
LEVEL     : Advanced
TOPIC     : Move semantics and the Rule of Five
YOU LEARN : - lvalues vs rvalues
            - move constructor and move assignment (steal instead of copy)
            - std::move
            - noexcept and why it matters for std::vector
            - Rule of Zero: the best rule of all

IDEA
Copying a big buffer is expensive. When the source is a temporary (about to be
destroyed anyway) we can simply STEAL its pointer. That is a "move".

RULE OF FIVE: if you manage a resource, define all five:
    destructor, copy ctor, copy assignment, move ctor, move assignment
RULE OF ZERO: better still, hold resources in std::vector / std::string /
smart pointers and write NONE of them - the defaults are correct.

EXERCISE : Print how many copies vs moves happen when you push_back 5 Buffers
           into a vector. Then remove `noexcept` from the move constructor and
           compare.
*/

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class Buffer
{
private:
    int* data;
    size_t size;

public:
    explicit Buffer(size_t n = 0) : data(n ? new int[n]() : nullptr), size(n)
    {
        cout << "  ctor      (size " << size << ")" << endl;
    }

    ~Buffer()
    {
        delete[] data;
    }

    // Copy constructor: expensive, duplicates the memory
    Buffer(const Buffer& other)
        : data(other.size ? new int[other.size] : nullptr), size(other.size)
    {
        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
        cout << "  COPY ctor (size " << size << ")" << endl;
    }

    // Copy assignment
    Buffer& operator=(const Buffer& other)
    {
        cout << "  COPY assignment" << endl;
        if (this != &other)
        {
            int* newData = other.size ? new int[other.size] : nullptr;
            for (size_t i = 0; i < other.size; i++)
                newData[i] = other.data[i];
            delete[] data;
            data = newData;
            size = other.size;
        }
        return *this;
    }

    // Move constructor: steal the pointer, leave the source empty but valid.
    // noexcept lets std::vector use moves when it grows (otherwise it copies).
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size)
    {
        other.data = nullptr;
        other.size = 0;
        cout << "  MOVE ctor (size " << size << ")" << endl;
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept
    {
        cout << "  MOVE assignment" << endl;
        if (this != &other)
        {
            delete[] data;              // release what we own
            data = other.data;          // steal
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    size_t getSize() const { return size; }
};

Buffer makeBuffer(size_t n)
{
    Buffer b(n);
    return b;           // moved (or elided entirely) - no deep copy
}

int main()
{
    cout << "1) Copy from a named object (lvalue):" << endl;
    Buffer a(1000);
    Buffer b = a;                       // copy ctor

    cout << "2) Move from a named object with std::move:" << endl;
    Buffer c = std::move(a);            // move ctor; `a` is now empty
    cout << "  a.size after move = " << a.getSize() << " (valid but empty)" << endl;

    cout << "3) Return from a function (rvalue):" << endl;
    Buffer d = makeBuffer(500);

    cout << "4) Move assignment:" << endl;
    Buffer e;
    e = makeBuffer(200);                // temporary -> move assignment

    cout << "5) push_back into a vector:" << endl;
    vector<Buffer> v;
    v.reserve(3);                       // avoid reallocation noise
    v.push_back(Buffer(10));            // temporary -> moved in
    v.push_back(b);                     // lvalue -> copied in
    v.push_back(std::move(c));          // explicit move

    cout << "Done. Sizes: d=" << d.getSize() << " e=" << e.getSize()
         << " v.size()=" << v.size() << endl;
    return 0;
}
