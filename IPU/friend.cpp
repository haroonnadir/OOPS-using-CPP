#include <iostream>
using namespace std;

class Memory;

class CPU
{
private:
    float cpuUtilization;

public:
    CPU(float cpu)
    {
        cpuUtilization = cpu;
    }

    friend void determineTask(CPU, Memory);
};

class Memory
{
private:
    float memoryUtilization;

public:
    Memory(float memory)
    {
        memoryUtilization = memory;
    }

    friend void determineTask(CPU, Memory);
};

// Friend function of both CPU and Memory
void determineTask(CPU c, Memory m)
{
    if (c.cpuUtilization < m.memoryUtilization)
    {
        cout << "CPU-intensive task may be started." << endl;
    }
    else if (m.memoryUtilization < c.cpuUtilization)
    {
        cout << "Memory-intensive task may be started." << endl;
    }
    else
    {
        cout << "CPU and memory utilization are equal." << endl;
    }
}

int main()
{
    float cpuValue, memoryValue;

    cout << "Enter CPU utilization: ";
    cin >> cpuValue;

    cout << "Enter memory utilization: ";
    cin >> memoryValue;

    CPU c(cpuValue);
    Memory m(memoryValue);

    determineTask(c, m);

    return 0;
}