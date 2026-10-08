/*
LEVEL     : Advanced
TOPIC     : Exception Handling
YOU LEARN : - try / throw / catch
            - the standard exception hierarchy (std::exception and friends)
            - writing your own exception class
            - catch order, catching by const reference, rethrowing
            - stack unwinding and why RAII makes code exception-safe
            - noexcept

IDEA
Exceptions separate "what to do when things work" from "what to do when they
do not". When a function throws, C++ unwinds the stack, destroying local
objects (their destructors run!) until a matching catch is found.

See also: IPU/matrix_multiplication.cpp (throws invalid_argument).

EXERCISE : Make withdraw() also throw when the amount is negative, using
           std::invalid_argument.
*/

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// ---------------------------------------------------------------------------
// Custom exception: derive from std::exception (or a subclass)
// ---------------------------------------------------------------------------
class InsufficientFunds : public runtime_error
{
private:
    double shortBy;

public:
    InsufficientFunds(double needed, double available)
        : runtime_error("Insufficient funds"), shortBy(needed - available) {}

    double getShortBy() const { return shortBy; }
};

class Account
{
private:
    double balance;

public:
    explicit Account(double b) : balance(b)
    {
        if (b < 0)
            throw invalid_argument("Opening balance cannot be negative");
    }

    void withdraw(double amount)
    {
        if (amount > balance)
            throw InsufficientFunds(amount, balance);
        balance -= amount;
    }

    double getBalance() const { return balance; }
};

// ---------------------------------------------------------------------------
// RAII + stack unwinding: the destructor still runs when an exception passes
// ---------------------------------------------------------------------------
class Guard
{
    string label;

public:
    explicit Guard(const string& l) : label(l) { cout << "  acquire " << label << endl; }
    ~Guard() { cout << "  release " << label << endl; }
};

void riskyWork()
{
    Guard g1("file");
    Guard g2("network");
    cout << "  about to throw..." << endl;
    throw runtime_error("something failed in riskyWork");
    // g2 then g1 are destroyed automatically while unwinding
}

// Rethrowing: log, then let someone else handle it
void middleLayer()
{
    try
    {
        riskyWork();
    }
    catch (const exception& e)
    {
        cout << "  middleLayer logged: " << e.what() << endl;
        throw;                          // rethrow the SAME exception
    }
}

// A function that promises never to throw (terminates if it does)
int safeAdd(int a, int b) noexcept
{
    return a + b;
}

int main()
{
    cout << "=== Custom exception ===" << endl;
    try
    {
        Account acc(100);
        acc.withdraw(30);
        cout << "Balance: " << acc.getBalance() << endl;
        acc.withdraw(500);              // throws
        cout << "never printed" << endl;
    }
    catch (const InsufficientFunds& e)  // most specific first
    {
        cout << "Caught: " << e.what() << ", short by " << e.getShortBy() << endl;
    }
    catch (const exception& e)          // general fallback
    {
        cout << "Other error: " << e.what() << endl;
    }

    cout << "\n=== Exception in constructor ===" << endl;
    try
    {
        Account bad(-5);
    }
    catch (const invalid_argument& e)
    {
        cout << "Caught: " << e.what() << endl;
    }

    cout << "\n=== Stack unwinding + rethrow ===" << endl;
    try
    {
        middleLayer();
    }
    catch (const exception& e)
    {
        cout << "main caught: " << e.what() << endl;
    }

    cout << "\n=== Standard exceptions ===" << endl;
    try
    {
        string s = "abc";
        cout << s.at(10);               // throws out_of_range
    }
    catch (const out_of_range& e)
    {
        cout << "out_of_range: " << e.what() << endl;
    }

    cout << "\nsafeAdd(2,3) = " << safeAdd(2, 3) << endl;

    /*
    GOOD HABITS
      * throw by value, catch by const reference
      * never throw from a destructor
      * use RAII (destructors / smart pointers) instead of try/finally
      * use exceptions for exceptional situations, not normal control flow
    */
    return 0;
}
