#include "Scheduler.hpp"
#include <algorithm>

Scheduler::Scheduler(std::vector<Process>& processes, int quantum)
    : processes(processes), quantum(quantum) {}

void Scheduler::runRoundRobin() {
    int completedCount = 0;
    time = 0;
    executionTimeline.clear();
    std::vector<Process*> readyQueue;

    for (auto& p : processes) {
        p.remainingTime = p.burstTime;
        p.completed = false;
    }

    while (completedCount < (int)processes.size()) {
        for (auto& p : processes) {
            if (p.arrivalTime <= time && p.remainingTime > 0 &&
                std::find(readyQueue.begin(), readyQueue.end(), &p) == readyQueue.end()) {
                readyQueue.push_back(&p);
            }
        }

        if (readyQueue.empty()) {
            executionTimeline.push_back(-1);
            time++;
            continue;
        }

        Process* p = readyQueue.front();
        readyQueue.erase(readyQueue.begin());

        int runTime = std::min(p->remainingTime, quantum);
        for (int i = 0; i < runTime; ++i) {
            executionTimeline.push_back(p->pid);
        }

        time += runTime;
        p->remainingTime -= runTime;

        if (p->remainingTime > 0) {
            readyQueue.push_back(p);
        } else {
            p->completed = true;
            completedCount++;
        }
    }
}

void Scheduler::runPriority() {
    int completedCount = 0;
    time = 0;
    executionTimeline.clear();

    for (auto& p : processes) {
        p.remainingTime = p.burstTime;
        p.completed = false;
    }

    while (completedCount < (int)processes.size()) {
        Process* next = nullptr;
        for (auto& p : processes) {
            if (!p.completed && p.arrivalTime <= time) {
                if (!next || p.priority < next->priority) {
                    next = &p;
                }
            }
        }

        if (!next) {
            executionTimeline.push_back(-1);
            time++;
            continue;
        }

        for (int i = 0; i < next->burstTime; ++i) {
            executionTimeline.push_back(next->pid);
        }
        time += next->burstTime;
        next->completed = true;
        completedCount++;
    }
}

void Scheduler::step() {
    if (mode == Algorithm::RoundRobin)
        runRoundRobin();
    else
        runPriority();
}

bool Scheduler::isFinished() const {
    return true;
}

const std::vector<int>& Scheduler::getTimeline() const {
    return executionTimeline;
}