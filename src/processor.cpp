#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    cpuData = LinuxParser::CpuUtilization();
    total = 0;
    for (auto val : cpuData)
        total += stof(val);
    nonIdle = total - stof(cpuData[LinuxParser::CPUStates::kIdle_]);
    return nonIdle/total; }