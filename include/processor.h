#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"


class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    float user, nice, system, idle, iowait, irq, softirq, steal, guest, guestNice, nonIdle, totalCpu; 
    std::string const filePath = LinuxParser::kProcDirectory + LinuxParser::kStatFilename;

};

#endif