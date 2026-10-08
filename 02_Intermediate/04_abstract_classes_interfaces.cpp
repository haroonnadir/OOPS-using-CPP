/*
LEVEL     : Intermediate
TOPIC     : Abstract Classes and Interfaces
YOU LEARN : - pure virtual functions (= 0)
            - an abstract class cannot be instantiated
            - an "interface" = a class with ONLY pure virtual functions
            - implementing several interfaces (C++ uses multiple inheritance)
            - programming to an interface (swap implementations freely)

IDEA
An abstract class defines WHAT must be done but not HOW. Every concrete
child must supply the HOW. This is exactly what IPU/stack_queue.cpp does with
LIST (store/retrieve).

EXERCISE : Add a NetBanking payment method and pay with it in main.
*/

#include <iostream>
#include <string>
using namespace std;

// An interface: pure virtual functions only, plus a virtual destructor
class Payable
{
public:
    virtual ~Payable() {}
    virtual bool pay(double amount) = 0;          // "= 0" => pure virtual
    virtual string describe() const = 0;
};

class Printable
{
public:
    virtual ~Printable() {}
    virtual void print() const = 0;
};

class CreditCard : public Payable
{
    double limit;

public:
    explicit CreditCard(double creditLimit) : limit(creditLimit) {}

    bool pay(double amount) override
    {
        if (amount > limit)
        {
            cout << "  Card declined: over limit." << endl;
            return false;
        }
        limit -= amount;
        cout << "  Paid " << amount << " by card. Remaining limit " << limit << endl;
        return true;
    }

    string describe() const override { return "Credit Card"; }
};

// Upi implements TWO interfaces: Payable and Printable
class Upi : public Payable, public Printable
{
    string upiId;
    double balance;

public:
    Upi(const string& id, double bal) : upiId(id), balance(bal) {}

    void print() const override
    {
        cout << "UPI account " << upiId << " balance " << balance << endl;
    }

    bool pay(double amount) override
    {
        if (amount > balance)
        {
            cout << "  UPI failed: insufficient balance." << endl;
            return false;
        }
        balance -= amount;
        cout << "  Paid " << amount << " via UPI (" << upiId << "). Balance " << balance << endl;
        return true;
    }

    string describe() const override { return "UPI"; }
};

class Cash : public Payable
{
public:
    bool pay(double amount) override
    {
        cout << "  Paid " << amount << " in cash." << endl;
        return true;
    }

    string describe() const override { return "Cash"; }
};

class Invoice : public Printable
{
    int number;
    double total;

public:
    Invoice(int n, double t) : number(n), total(t) {}

    double getTotal() const { return total; }

    void print() const override
    {
        cout << "Invoice #" << number << " total = " << total << endl;
    }
};

// This function knows NOTHING about cards, UPI or cash. It only needs a Payable.
// New payment methods can be added without changing checkout().
bool checkout(Payable& method, const Invoice& invoice)
{
    cout << "Paying with " << method.describe() << ":" << endl;
    return method.pay(invoice.getTotal());
}

int main()
{
    // Payable p;   // ERROR: cannot instantiate an abstract class

    Invoice inv(101, 2500);
    inv.print();

    CreditCard card(2000);
    Upi upi("riya@bank", 10000);
    Cash cash;

    checkout(card, inv);      // fails: limit is only 2000
    checkout(upi, inv);       // works
    checkout(cash, inv);      // works

    upi.print();              // Upi is also a Printable

    return 0;
}
