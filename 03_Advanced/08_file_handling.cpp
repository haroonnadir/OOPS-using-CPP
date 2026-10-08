/*
LEVEL     : Advanced
TOPIC     : File Handling with Objects
YOU LEARN : - ofstream (write) and ifstream (read)
            - checking that a file opened
            - appending with ios::app
            - saving and loading objects as text lines (serialization)
            - binary files with write() / read()
            - RAII: files close automatically when the stream object dies

IDEA
To make objects persist after the program ends, write them to a file. A
simple, human-readable approach is one object per line.

The program creates a small temporary file in the current folder and deletes
it again at the end, so nothing is left behind.

EXERCISE : Add a function that updates one student's marks in the file.
*/

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Student
{
private:
    int roll;
    string name;
    double marks;

public:
    Student() : roll(0), name(""), marks(0) {}
    Student(int r, const string& n, double m) : roll(r), name(n), marks(m) {}

    // Serialize: "roll,name,marks"
    string toLine() const
    {
        ostringstream out;
        out << roll << "," << name << "," << marks;
        return out.str();
    }

    // Deserialize
    static Student fromLine(const string& line)
    {
        istringstream in(line);
        string rollText, name, marksText;
        getline(in, rollText, ',');
        getline(in, name, ',');
        getline(in, marksText, ',');
        return Student(stoi(rollText), name, stod(marksText));
    }

    void print() const
    {
        cout << "  Roll " << roll << " | " << name << " | " << marks << endl;
    }
};

// A plain struct is safe to dump as raw bytes (no pointers, no std::string)
struct Record
{
    int id;
    double score;
};

void saveStudents(const string& path, const vector<Student>& list)
{
    ofstream file(path);                       // truncates the file
    if (!file)
    {
        cout << "Cannot open " << path << " for writing" << endl;
        return;
    }
    for (const auto& s : list)
        file << s.toLine() << "\n";
}   // file closes automatically here (RAII)

void appendStudent(const string& path, const Student& s)
{
    ofstream file(path, ios::app);             // append mode
    if (file)
        file << s.toLine() << "\n";
}

vector<Student> loadStudents(const string& path)
{
    vector<Student> list;
    ifstream file(path);
    if (!file)
    {
        cout << "Cannot open " << path << " for reading" << endl;
        return list;
    }

    string line;
    while (getline(file, line))
    {
        if (!line.empty())
            list.push_back(Student::fromLine(line));
    }
    return list;
}

int main()
{
    const string textPath = "students_demo.txt";
    const string binPath = "records_demo.bin";

    cout << "=== Text file: save, append, load ===" << endl;
    saveStudents(textPath, {Student(1, "Aman", 78.5), Student(2, "Riya", 92)});
    appendStudent(textPath, Student(3, "Kabir", 35));

    for (const auto& s : loadStudents(textPath))
        s.print();

    cout << "\n=== Binary file ===" << endl;
    {
        ofstream out(binPath, ios::binary);
        Record r1{7, 88.5}, r2{8, 61.0};
        out.write(reinterpret_cast<const char*>(&r1), sizeof(Record));
        out.write(reinterpret_cast<const char*>(&r2), sizeof(Record));
    }
    {
        ifstream in(binPath, ios::binary);
        Record r;
        while (in.read(reinterpret_cast<char*>(&r), sizeof(Record)))
            cout << "  id=" << r.id << " score=" << r.score << endl;
    }

    cout << "\n=== Reading a file that does not exist ===" << endl;
    loadStudents("no_such_file.txt");

    // Clean up the demo files
    remove(textPath.c_str());
    remove(binPath.c_str());
    cout << "\nDemo files removed." << endl;

    return 0;
}
