#include <iostream>
using namespace std;

class LIST
{
public:
    // Virtual destructor: required so deleting a derived object
    // through a LIST* calls the derived destructor too.
    virtual ~LIST() {}

    virtual void store(int value) = 0;
    virtual int retrieve() = 0;
};

class stack : public LIST
{
private:
    int arr[10];
    int top;

public:
    stack()
    {
        top = -1;
    }

    void store(int value) override
    {
        if (top == 9)
        {
            cout << "Stack is full." << endl;
            return;
        }

        arr[++top] = value;
    }

    int retrieve() override
    {
        if (top == -1)
        {
            cout << "Stack is empty." << endl;
            return -1;
        }

        return arr[top--];
    }
};

class queue : public LIST
{
private:
    int arr[10];
    int front, rear;

public:
    queue()
    {
        front = 0;
        rear = -1;
    }

    void store(int value) override
    {
        if (rear == 9)
        {
            cout << "Queue is full." << endl;
            return;
        }

        arr[++rear] = value;
    }

    int retrieve() override
    {
        if (front > rear)
        {
            cout << "Queue is empty." << endl;
            return -1;
        }

        return arr[front++];
    }
};

int main()
{
    stack s;
    queue q;

    cout << "Stack:" << endl;

    s.store(10);
    s.store(20);
    s.store(30);

    cout << "Retrieved: " << s.retrieve() << endl;
    cout << "Retrieved: " << s.retrieve() << endl;

    cout << "\nQueue:" << endl;

    q.store(10);
    q.store(20);
    q.store(30);

    cout << "Retrieved: " << q.retrieve() << endl;
    cout << "Retrieved: " << q.retrieve() << endl;

    return 0;
}
