#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>
#include "Process.hpp"

enum class Algorithm {
    RoundRobin,
    Priority
};


class Scheduler{
public:
    Scheduler(std::vector<Process>& processes, int quantum);
    void step();
    void draw();
    bool isFinished() const;

    std::vector<Process> getExecutionOrder() const;

public:
    const std::vector<int>& getTimeline() const;

private:
    std::vector<Process>& processes;
    std::vector<int> executionTimeline;
    int time = 0;
    int quantum;
    Algorithm mode;

    void runRoundRobin();
    void runPriority();
};



#endif