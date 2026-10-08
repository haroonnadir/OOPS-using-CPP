/*
LEVEL     : Advanced
TOPIC     : Common Design Patterns
YOU LEARN : - Singleton  : exactly one instance, globally reachable
            - Factory    : create objects without naming the concrete class
            - Strategy   : swap an algorithm at run time
            - Observer   : notify many listeners when something changes

IDEA
Design patterns are named, reusable solutions to problems that appear again
and again in OOP. They are built from what you already learned: classes,
inheritance, virtual functions and composition.

NOTE: needs C++14 or later.

EXERCISE : Add a new Strategy (e.g. FestivalDiscount 30%) and a new Observer
           (e.g. SmsAlert) without modifying existing classes.
*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// ===========================================================================
// 1. SINGLETON
// ===========================================================================
class Logger
{
private:
    int lines = 0;

    Logger() { cout << "  (Logger created once)" << endl; }   // private ctor

public:
    Logger(const Logger&) = delete;               // no copies
    Logger& operator=(const Logger&) = delete;

    static Logger& instance()
    {
        static Logger theOnlyOne;                 // created on first use, thread-safe in C++11+
        return theOnlyOne;
    }

    void log(const string& msg) { cout << "  [LOG " << ++lines << "] " << msg << endl; }
};

// ===========================================================================
// 2. FACTORY
// ===========================================================================
class Vehicle
{
public:
    virtual ~Vehicle() {}
    virtual string wheels() const = 0;
};

class Bike : public Vehicle
{
public:
    string wheels() const override { return "Bike: 2 wheels"; }
};

class Car : public Vehicle
{
public:
    string wheels() const override { return "Car: 4 wheels"; }
};

class Truck : public Vehicle
{
public:
    string wheels() const override { return "Truck: 6 wheels"; }
};

unique_ptr<Vehicle> makeVehicle(const string& kind)
{
    if (kind == "bike")  return make_unique<Bike>();
    if (kind == "car")   return make_unique<Car>();
    if (kind == "truck") return make_unique<Truck>();
    return nullptr;
}

// ===========================================================================
// 3. STRATEGY
// ===========================================================================
class DiscountStrategy
{
public:
    virtual ~DiscountStrategy() {}
    virtual double apply(double price) const = 0;
};

class NoDiscount : public DiscountStrategy
{
public:
    double apply(double price) const override { return price; }
};

class PercentDiscount : public DiscountStrategy
{
    double percent;

public:
    explicit PercentDiscount(double p) : percent(p) {}
    double apply(double price) const override { return price * (1 - percent / 100); }
};

class FlatDiscount : public DiscountStrategy
{
    double amount;

public:
    explicit FlatDiscount(double a) : amount(a) {}
    double apply(double price) const override { return price > amount ? price - amount : 0; }
};

class Cart
{
    double total = 0;
    unique_ptr<DiscountStrategy> strategy = make_unique<NoDiscount>();

public:
    void add(double price) { total += price; }
    void setStrategy(unique_ptr<DiscountStrategy> s) { strategy = std::move(s); }
    double checkout() const { return strategy->apply(total); }
};

// ===========================================================================
// 4. OBSERVER
// ===========================================================================
class Observer
{
public:
    virtual ~Observer() {}
    virtual void update(const string& product, double newPrice) = 0;
};

class PriceTracker           // the "subject"
{
    vector<Observer*> observers;

public:
    void subscribe(Observer* o) { observers.push_back(o); }

    void setPrice(const string& product, double price)
    {
        cout << "  Price of " << product << " is now " << price << endl;
        for (Observer* o : observers)
            o->update(product, price);          // notify everyone
    }
};

class EmailAlert : public Observer
{
public:
    void update(const string& product, double newPrice) override
    {
        cout << "    email: " << product << " now costs " << newPrice << endl;
    }
};

class AppNotification : public Observer
{
public:
    void update(const string& product, double newPrice) override
    {
        cout << "    push : " << product << " -> " << newPrice << endl;
    }
};

int main()
{
    cout << "=== Singleton ===" << endl;
    Logger::instance().log("program started");
    Logger::instance().log("same object again");

    cout << "\n=== Factory ===" << endl;
    for (const string kind : {"bike", "car", "truck", "plane"})
    {
        auto v = makeVehicle(kind);
        cout << "  " << (v ? v->wheels() : "Unknown vehicle '" + kind + "'") << endl;
    }

    cout << "\n=== Strategy ===" << endl;
    Cart cart;
    cart.add(1000);
    cart.add(500);
    cout << "  no discount : " << cart.checkout() << endl;
    cart.setStrategy(make_unique<PercentDiscount>(10));
    cout << "  10% off     : " << cart.checkout() << endl;
    cart.setStrategy(make_unique<FlatDiscount>(200));
    cout << "  flat 200 off: " << cart.checkout() << endl;

    cout << "\n=== Observer ===" << endl;
    PriceTracker tracker;
    EmailAlert email;
    AppNotification app;
    tracker.subscribe(&email);
    tracker.subscribe(&app);
    tracker.setPrice("Laptop", 54999);

    return 0;
}
