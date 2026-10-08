/*
LEVEL     : Beginner
TOPIC     : Encapsulation, Access Specifiers, Getters and Setters
YOU LEARN : - public vs private vs protected
            - hiding data and exposing a safe interface
            - validating input inside setters / methods
            - const member functions (getters that do not modify the object)

IDEA
Encapsulation = keep the data private, and let the outside world touch it only
through public functions. Those functions can enforce rules (e.g. balance can
never go negative). If data were public, anyone could break the rules.

See also: PRACTICE/rect.cpp (setters).

EXERCISE : Add a method transferTo(BankAccount& other, double amount).
*/

#include <iostream>
#include <string>
using namespace std;

class BankAccount
{
private:                      // only code inside this class can touch these
    string owner;
    double balance;

public:
    BankAccount(const string& ownerName, double openingBalance = 0)
        : owner(ownerName), balance(0)
    {
        if (openingBalance > 0)
            balance = openingBalance;
    }

    // Getters are const: they promise not to change the object
    string getOwner() const { return owner; }
    double getBalance() const { return balance; }

    // Setter with validation
    bool setOwner(const string& newName)
    {
        if (newName.empty())
        {
            cout << "  Rejected: name cannot be empty." << endl;
            return false;
        }
        owner = newName;
        return true;
    }

    bool deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "  Rejected: deposit must be positive." << endl;
            return false;
        }
        balance += amount;
        return true;
    }

    bool withdraw(double amount)
    {
        if (amount <= 0 || amount > balance)
        {
            cout << "  Rejected: invalid amount or insufficient funds." << endl;
            return false;
        }
        balance -= amount;
        return true;
    }
};

int main()
{
    BankAccount acc("Aman", 1000);

    cout << "Owner: " << acc.getOwner() << ", balance: " << acc.getBalance() << endl;

    // acc.balance = 1000000;   // ERROR: 'balance' is private. Try un-commenting!

    cout << "Deposit 500:" << endl;
    acc.deposit(500);

    cout << "Withdraw 5000 (too much):" << endl;
    acc.withdraw(5000);

    cout << "Deposit -50 (invalid):" << endl;
    acc.deposit(-50);

    cout << "Rename to empty string:" << endl;
    acc.setOwner("");

    acc.setOwner("Aman Kumar");
    cout << "Final -> " << acc.getOwner() << ": " << acc.getBalance() << endl;

    /*
    ACCESS SPECIFIERS - quick table
      specifier   same class   derived class   outside
      public         yes           yes           yes
      protected      yes           yes           no
      private        yes           no            no
    (In a `class`, members are private by default; in a `struct`, public.)
    */
    return 0;
}
