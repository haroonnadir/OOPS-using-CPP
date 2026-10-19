 # OOPS-using-CPP — Beginner to Advanced

A hands-on course in Object-Oriented Programming with C++. Every lesson is one
small, heavily commented `.cpp` file that you can compile and run on its own.
Read the comment block at the top of a file, run it, change the code, then
try the **EXERCISE** at the bottom of that block.

Repository: <https://github.com/haroonnadir/OOPS-using-CPP>

## How to compile and run

You need a C++17 compiler (g++ 9+, clang 10+ or MSVC 2019+).

```bash
# get the code
git clone https://github.com/haroonnadir/OOPS-using-CPP.git
cd OOPS-using-CPP
```

```bash
# one file
g++ -std=c++17 -Wall -Wextra 01_Beginner/01_class_and_object.cpp -o demo
./demo            # on Windows: demo.exe
```

## Learning path

Follow the folders in order. Each lesson builds on the previous ones.

### Level 1 — Beginner (`01_Beginner/`)

| # | File | You learn |
|---|------|-----------|
| 1 | `01_class_and_object.cpp` | classes, objects, `.` and `->`, arrays of objects |
| 2 | `02_constructors_destructors.cpp` | default / parameterized / copy / delegating constructors, destructor order |
| 3 | `03_encapsulation_getters_setters.cpp` | `public` / `private`, validation, getters and setters |
| 4 | `04_this_pointer_and_static_members.cpp` | `this`, method chaining, `static` data and functions |
| 5 | `05_references_pointers_const.cpp` | pass by value / reference / `const&`, `const` methods, `mutable` |

### Level 2 — Intermediate (`02_Intermediate/`)

| # | File | You learn |
|---|------|-----------|
| 1 | `01_operator_overloading.cpp` | `+ - == << >> ++ []`, what can and cannot be overloaded |
| 2 | `02_inheritance.cpp` | single / multilevel / hierarchical inheritance, `protected`, ctor order |
| 3 | `03_polymorphism_virtual.cpp` | overloading, `virtual`, `override`, `final`, virtual destructor, slicing |
| 4 | `04_abstract_classes_interfaces.cpp` | pure virtual functions, interfaces, programming to an interface |
| 5 | `05_friend_composition_aggregation.cpp` | `friend`, "has-a" relationships, composition vs aggregation |
| 6 | `06_deep_copy_rule_of_three.cpp` | shallow vs deep copy, destructor + copy ctor + copy assignment |

### Level 3 — Advanced (`03_Advanced/`)

| # | File | You learn |
|---|------|-----------|
| 1 | `01_rule_of_five_move_semantics.cpp` | rvalues, move constructor/assignment, `std::move`, `noexcept` |
| 2 | `02_templates.cpp` | function/class templates, specialization, variadic templates |
| 3 | `03_exception_handling.cpp` | `try/catch/throw`, custom exceptions, stack unwinding, RAII |
| 4 | `04_smart_pointers_raii.cpp` | `unique_ptr`, `shared_ptr`, `weak_ptr`, breaking cycles |
| 5 | `05_stl_and_lambdas.cpp` | `vector`, `map`, `set`, algorithms, lambdas, structured bindings |
| 6 | `06_multiple_inheritance_diamond.cpp` | ambiguity, the diamond problem, virtual inheritance |
| 7 | `07_design_patterns.cpp` | Singleton, Factory, Strategy, Observer |
| 8 | `08_file_handling.cpp` | `ifstream` / `ofstream`, saving objects, binary files |
| 9 | `09_mini_project_library_system.cpp` | capstone: everything combined in one program |

### Original assignments (kept as practice and reference)

These are the original lab programs. Each one maps to a lesson above:

| File | Related lesson |
|------|----------------|
| `IPU/complex.cpp` | Beginner 2 (constructor overloading), Intermediate 1 (operator overloading) |
| `IPU/friend.cpp` | Intermediate 5 (friend functions) |
| `IPU/matrix_multiplication.cpp` | Intermediate 6 (deep copy, Rule of Three), Advanced 3 (exceptions) |
| `IPU/stack_queue.cpp` | Intermediate 3 and 4 (abstract class, polymorphism), Advanced 2 (templates) |
| `PRACTICE/distance.cpp` | Beginner 2 (constructors) |
| `PRACTICE/rect.cpp` | Beginner 3 (encapsulation, setters) |

`IPU/matrix_multiplication.cpp` and `IPU/friend.cpp` read input from the keyboard;
all other programs run without input.

## The four pillars of OOP, and where to find them

| Pillar | Meaning | Lesson |
|--------|---------|--------|
| Encapsulation | Hide data, expose a safe interface | Beginner 3 |
| Abstraction | Show *what*, hide *how* | Intermediate 4 |
| Inheritance | Reuse and extend existing classes | Intermediate 2 |
| Polymorphism | One interface, many behaviours | Intermediate 3 |

## Suggested way to study

1. Read the header comment, then read the code top to bottom.
2. Predict the output **before** running the program.
3. Run it and compare. Where you were wrong is where you learn most.
4. Break the code on purpose (the comments mark good places to try) and read the compiler error.
5. Solve the EXERCISE in the header, then compare with your own solution.
6. After Level 3, extend the capstone project using its exercise ideas.

## Coding conventions used here

* C++17, no external libraries
* One concept per file, one `main()` per file
* Beginner files use plain loops and raw pointers on purpose, so you see what
  is happening. Advanced files show the modern way (smart pointers, STL, RAII).
