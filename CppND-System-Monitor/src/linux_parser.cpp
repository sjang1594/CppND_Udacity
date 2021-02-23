#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

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
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
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

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float memTotal = 0.0;
  float memFree = 0.0;
  string line;
  string key;
  string val;

  //read file from /proc/meminfo and find MEMTOTAL and MEMFREE
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){

      //remove 'kb' at the end
      std::remove(line.begin(), line.end(), ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);

      while(linestream >> key >> val){
        //search for key memTotal
        if(key == "MemTotal"){
          memTotal = std::stof(val);
        }
        else if (key == "MemFree"){
          memFree = std::stof(val);
          break;
        }
      }
    }
  }
  return ((memTotal - memFree) / memTotal); 
}

// Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  string TotalTime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      while(linestream >> TotalTime){
        try{
          return std::stol(TotalTime);
        }catch(const std::invalid_argument& arg){
          return 0;
        }
      }
    }
  }
  
   return 0; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpuValues{};
  string line;
  string key;
  string vuser, vnice, vsystem, vidle, viowait, virq, vsoftirq, vsteal, vguest, vguest_nice;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      while(linestream >> key >> vuser >> vnice >> vsystem >> vidle >> viowait >> virq >> vsoftirq >> vsteal
      >> vguest >> vguest_nice){
        if(key == "cpu"){
          cpuValues.push_back(vuser);
          cpuValues.push_back(vnice);
          cpuValues.push_back(vsystem);
          cpuValues.push_back(vidle);
          cpuValues.push_back(viowait);
          cpuValues.push_back(virq);
          cpuValues.push_back(vsoftirq);
          cpuValues.push_back(vsteal);
          cpuValues.push_back(vguest);
          cpuValues.push_back(vguest_nice);
          return cpuValues;
        }
      }
    }
  }

  return {}; 
  }

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string val;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      while(linestream >> key >> val){
        if(key == "processes"){

          try{
            return std::stol(val);
          }catch (const std::invalid_argument& arg){
            return 0;
          }

        }
      }
    }
  }
   return 0; 
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string val;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()){
    std::istringstream linestream(line);
    while(linestream >> key >> val)
    {
      if(key == "procs_running"){
        try{
          return std::stol(val);
        }catch (const std::invalid_argument& arg){
          return 0;
        }
      }
    }
    
  }
   return 0; 
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string val = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);
  if(filestream.is_open()){
    std::getline(filestream, val);
    return val;
  }
   return val; 
}

// Read CPU usage of a process and return the time.
vector<float> LinuxParser::CpuUtilization(int pid){
  vector<float> cpuValues{};
  string line;
  float time = 0;
  string val;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);

  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      for (int i = 1; i <= kStarttime_; i++){
        linestream >> val;

        //read CPU time spent in user mode - utime #14
        //read CPU time spend in kernel mode -stime #15
        //read waited for children's CPU time spent in user mode - cutime #16
        //read waited for children's CPU time spent in kernel mode - cstime #17
        //read the time when process started - starttime #22

        if(i == kUtime_ || i == kStime_ || i == kCutime_|| i == kCstime_ || i == kStarttime_){
          //read the clock ticks and convert to secs
          //devide by clock ticks per secs
          time = std::stof(val) / sysconf(_SC_CLK_TCK);
          cpuValues.push_back(time);
        }
      }
    }
  }
  return cpuValues;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line;
  string key;
  string val = "";

  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> key >> val){
        if(key  == "VmSize"){
          return val;
        }
      }
    }
  }
   return val;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string val = "";

  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> key >> val){
        if(key  == "Uid"){
          return val;
        }
      }
    }
  }
   return val;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string uid = Uid(pid);
  string line;
  string key;
  string val = "";
  string dst;

  // find the user name for this UID in /etc/passwd
  std::ifstream filestream(kPasswordPath);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> val >> dst >> key){
        if(key  == uid){
          return val;
        }
      }
    }
  }
   return val;  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line;
  long uptime = 0;
  string val;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);

  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      for (int i = 1; i <= kStarttime_; i++){
        linestream >> val;
        if(i == kStarttime_){
          //read the start time value in clock ticks and convert to seconds
          //divide by clock ticks per second
          try{
            uptime = std::stol(val) / sysconf(_SC_CLK_TCK);
            return uptime;
          }
          catch (const std::invalid_argument& arg){
            return 0;
          }
        }
      }
    }
  } 
  return uptime; 
  }