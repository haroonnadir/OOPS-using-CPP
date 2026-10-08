/*
LEVEL     : Advanced
TOPIC     : STL containers, algorithms and lambdas
YOU LEARN : - vector, map, unordered_map, set
            - range-based for, auto, structured bindings (C++17)
            - lambda expressions and captures
            - <algorithm>: sort, find_if, count_if, transform, remove_if
            - <numeric>: accumulate
            - the erase-remove idiom

IDEA
The Standard Template Library already contains well-tested versions of the
data structures you wrote by hand (stack, queue, arrays). Real C++ code uses
them with algorithms instead of hand-written loops.

NOTE: needs C++17.

EXERCISE : Print the names of all students who scored above the class average.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Student
{
public:
    string name;
    int marks;

    Student(const string& n, int m) : name(n), marks(m) {}
};

int main()
{
    vector<Student> students = {
        {"Aman", 78}, {"Riya", 92}, {"Kabir", 35}, {"Sara", 64}, {"Neha", 92}};

    cout << "=== sort with a lambda (highest marks first, then by name) ===" << endl;
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.marks != b.marks)
            return a.marks > b.marks;
        return a.name < b.name;
    });
    for (const auto& s : students)
        cout << "  " << s.name << " " << s.marks << endl;

    cout << "\n=== count_if / find_if / accumulate ===" << endl;
    int passed = (int)count_if(students.begin(), students.end(),
                               [](const Student& s) { return s.marks >= 40; });
    cout << "Passed: " << passed << " of " << students.size() << endl;

    auto firstFail = find_if(students.begin(), students.end(),
                             [](const Student& s) { return s.marks < 40; });
    if (firstFail != students.end())
        cout << "First failing student: " << firstFail->name << endl;

    int total = accumulate(students.begin(), students.end(), 0,
                           [](int sum, const Student& s) { return sum + s.marks; });
    double average = static_cast<double>(total) / students.size();
    cout << "Average: " << average << endl;

    cout << "\n=== lambda captures ===" << endl;
    int threshold = 80;
    auto aboveThreshold = [threshold](const Student& s) { return s.marks > threshold; };
    cout << "Above " << threshold << ": ";
    for (const auto& s : students)
        if (aboveThreshold(s))
            cout << s.name << " ";
    cout << endl;

    cout << "\n=== transform: add 5 grace marks (capped at 100) ===" << endl;
    vector<int> marks;
    for (const auto& s : students)
        marks.push_back(s.marks);
    transform(marks.begin(), marks.end(), marks.begin(),
              [](int m) { return min(m + 5, 100); });
    for (int m : marks)
        cout << m << " ";
    cout << endl;

    cout << "\n=== erase-remove idiom ===" << endl;
    students.erase(remove_if(students.begin(), students.end(),
                             [](const Student& s) { return s.marks < 40; }),
                   students.end());
    cout << "After removing failures: " << students.size() << " students" << endl;

    cout << "\n=== map (sorted by key) ===" << endl;
    map<string, int> marksByName;
    for (const auto& s : students)
        marksByName[s.name] = s.marks;
    for (const auto& [name, mark] : marksByName)        // structured bindings
        cout << "  " << name << " -> " << mark << endl;

    cout << "\n=== unordered_map (hash table, average O(1) lookup) ===" << endl;
    unordered_map<string, int> lookup(marksByName.begin(), marksByName.end());
    if (lookup.count("Riya"))
        cout << "Riya scored " << lookup["Riya"] << endl;
    cout << "Zed present? " << (lookup.find("Zed") != lookup.end() ? "yes" : "no") << endl;

    cout << "\n=== set (unique, sorted) ===" << endl;
    set<int> uniqueMarks;
    for (const auto& s : students)
        uniqueMarks.insert(s.marks);
    for (int m : uniqueMarks)
        cout << m << " ";
    cout << "\n(duplicate 92 stored once)" << endl;

    return 0;
}
