/*
LEVEL     : Advanced
TOPIC     : Templates (generic programming)
YOU LEARN : - function templates
            - class templates (a generic Stack<T>)
            - template specialization
            - non-type template parameters
            - variadic templates + fold expressions (C++17)

IDEA
A template is a blueprint for code. The compiler writes the real class or
function for each type you use, so ONE Stack<T> works for int, string, ...

Compare with IPU/stack_queue.cpp, which is hard-wired to int and size 10.

NOTE: needs C++17.  g++ -std=c++17 02_templates.cpp -o templates

EXERCISE : Turn Stack<T> into Queue<T> using std::deque.
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------
// 1. Function template
// ---------------------------------------------------------------------------
template <typename T>
T maxOf(const T& a, const T& b)
{
    return (a > b) ? a : b;
}

// ---------------------------------------------------------------------------
// 2. Class template: a growable stack for ANY type
// ---------------------------------------------------------------------------
template <typename T>
class Stack
{
private:
    vector<T> items;

public:
    void push(const T& value) { items.push_back(value); }

    T pop()
    {
        if (items.empty())
            throw underflow_error("Stack is empty");
        T top = items.back();
        items.pop_back();
        return top;
    }

    const T& peek() const
    {
        if (items.empty())
            throw underflow_error("Stack is empty");
        return items.back();
    }

    bool empty() const { return items.empty(); }
    size_t size() const { return items.size(); }
};

// ---------------------------------------------------------------------------
// 3. Template specialization: special behaviour for one particular type
// ---------------------------------------------------------------------------
template <typename T>
struct Describer
{
    static string describe(const T&) { return "some value"; }
};

template <>
struct Describer<bool>
{
    static string describe(const bool& b) { return b ? "TRUE" : "FALSE"; }
};

// ---------------------------------------------------------------------------
// 4. Non-type parameter: the size is part of the type (checked at compile time)
// ---------------------------------------------------------------------------
template <typename T, size_t N>
class FixedArray
{
private:
    T data[N];

public:
    FixedArray()
    {
        for (size_t i = 0; i < N; i++)
            data[i] = T();
    }

    T& operator[](size_t i)
    {
        if (i >= N)
            throw out_of_range("FixedArray index out of range");
        return data[i];
    }

    constexpr size_t size() const { return N; }
};

// ---------------------------------------------------------------------------
// 5. Variadic template + C++17 fold expression: sum any number of arguments
// ---------------------------------------------------------------------------
template <typename... Args>
auto sumAll(Args... args)
{
    return (args + ...);        // fold: a + b + c + ...
}

int main()
{
    cout << "=== Function template ===" << endl;
    cout << maxOf(3, 7) << endl;
    cout << maxOf(2.5, 1.5) << endl;
    cout << maxOf(string("apple"), string("mango")) << endl;

    cout << "\n=== Class template ===" << endl;
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    cout << "peek=" << s.peek() << ", pop=" << s.pop() << ", pop=" << s.pop()
         << ", size=" << s.size() << endl;

    Stack<string> words;
    words.push("hello");
    words.push("world");
    cout << words.pop() << " " << words.pop() << endl;

    try
    {
        words.pop();                    // empty -> exception
    }
    catch (const underflow_error& e)
    {
        cout << "Caught: " << e.what() << endl;
    }

    cout << "\n=== Specialization ===" << endl;
    cout << Describer<int>::describe(5) << endl;
    cout << Describer<bool>::describe(true) << endl;

    cout << "\n=== Non-type parameter ===" << endl;
    FixedArray<int, 4> arr;
    arr[0] = 9;
    cout << "size=" << arr.size() << ", arr[0]=" << arr[0] << endl;

    cout << "\n=== Variadic ===" << endl;
    cout << sumAll(1, 2, 3, 4) << endl;
    cout << sumAll(1.5, 2.5) << endl;

    return 0;
}
