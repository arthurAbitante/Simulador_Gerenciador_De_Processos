#include "Process.hpp"

Process::Process(int id, int arrival, int burst, int prio)
    : pid(id), arrivalTime(arrival), burstTime(burstTime),
        remainingTime(burst), priority(prio), completed(false){}