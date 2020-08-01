#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line, key, value, filename = kProcDirectory + kMeminfoFilename;;
  float memTotal, memFree;
    
  std::ifstream filestream(filename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:")
        memTotal = stof(value);
      else if (key == "MemFree:")
        memFree = stof(value);
    }
  }
  return (memTotal - memFree)/(memTotal);
  } 

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line, upTime, filename = kProcDirectory + kUptimeFilename;
  long activeTime;

  std::ifstream filestream(filename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> upTime;
    activeTime = stol(upTime);
  }
  return activeTime; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line, key, value, filename = kProcDirectory + kStatFilename;
  vector<string> cpuVals;
  std::ifstream filestream(filename);
  if (filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line); 
    linestream >> key; 
    if (key == "cpu"){
      for (int val = kUser_;  val != kGuestNice_+1; val++) {
        linestream >> value; 
        cpuVals.push_back(value);
      }
    return cpuVals;
    }
  }
  


  return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key, value, line, filename = kProcDirectory + kStatFilename;

  std::ifstream filestream(filename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes"){
        return stoi(value);
      }
    }
  }
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key, value, line, filename = kProcDirectory + kStatFilename;

  std::ifstream filestream(filename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running"){
        return stoi(value);
      }
    }
  }
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line, cmdline, filename = kProcDirectory + std::to_string(pid) + kCmdlineFilename;
  std::ifstream filestream(filename);
  if(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> line; 
    cmdline += line;
  }
  return cmdline; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line, key, value, filename = kProcDirectory + std::to_string(pid) + kStatusFilename;
  std::ifstream filestream(filename);
  if(filestream.is_open()) {
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value; 
      if (key == "VmSize:")
        return std::to_string((stoi(value)/1024));
    }
  }
  return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }