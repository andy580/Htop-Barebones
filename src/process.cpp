#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    std::vector <string> pJifs = LinuxParser::CpuUtilization(pid_);
    float utime, stime, cutime, cstime, starttime, totaltime, pCpuUtil, seconds;
    utime = stof(pJifs[0]);
    stime = stof(pJifs[1]);
    cutime = stof(pJifs[2]);
    cstime = stof(pJifs[3]);
    starttime = stof(pJifs[4]);
    totaltime = utime + stime + cutime + cstime;
    totaltime /= (float)sysconf(_SC_CLK_TCK);
    
    float procUptime = starttime / (float)sysconf(_SC_CLK_TCK);
    seconds = LinuxParser::UpTime() - procUptime;
    pCpuUtil = totaltime / seconds;
    return pCpuUtil; }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
   return (a.memory) < (this->memory); }