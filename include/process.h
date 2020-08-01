#ifndef PROCESS_H
#define PROCESS_H

#include "linux_parser.h"
#include <string>
#include <typeinfo>
#include <iostream>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process (int pid) : pid_(pid) {
      ram_ = Ram();
      if (ram_.size()<=0 || ram_.length()<=0){
          memory = 0;
      }
      else {
          memory = stof(ram_);
      }
        
    };
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

   // TODO: Declare any necessary private members
 private:
 int pid_;
 std::string ram_;
 float memory;
 
};

#endif