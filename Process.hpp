#ifndef PROCESS_HPP
#define PROCESS_HPP

class Process {
public:
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    bool completed;

    Process(int id, int arrival, int burst, int prio);
};

#endif