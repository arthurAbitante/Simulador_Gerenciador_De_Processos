#include "Process.hpp"

Process::Process()
    : pid(0), arrivalTime(0), burstTime(0), remainingTime(0),
      priority(0), completed(false) {}

Process::Process(int id, int arrival, int burst, int prio)
    : pid(id), arrivalTime(arrival), burstTime(burst),
      remainingTime(burst), priority(prio), completed(false) {}