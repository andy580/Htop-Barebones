#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::ifstream filestream(filePath);
    std::string line, cpuName; 
    float cpuUtil; 
    if(!filestream.is_open()){
        return -99;
    } else {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> cpuName >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guestNice;
        nonIdle = user + nice + system + iowait + irq + softirq + steal + guest + guestNice;
        totalCpu = idle + nonIdle;
        cpuUtil = nonIdle/totalCpu; 
    }

    return cpuUtil; }