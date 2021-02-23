#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

//Declare the constructor.
Process::Process(int pid) : processId_(pid){
    calculateCpuUsage();
    determineCommand();
    determineRam();
    determineUptime();
    determineUser();
};

// Return this process's ID
int Process::Pid() { return processId_; }

// Return this process's CPU utilization
float Process::CpuUtilization() const { return cpuUsage_; }

// Return the command that generated this process
string Process::Command() { return command_; }

// Return this process's memory utilization
string Process::Ram() { return ram_; }

// Return the user (name) that generated this process
string Process::User() { return user_; }

// Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

void Process::calculateCpuUsage(){
    long uptime = LinuxParser::UpTime();
    std::vector<float> val = LinuxParser::CpuUtilization(Pid());

    // if value can be read successfully
    if(val.size() == 5){
        //add uptime
        float total_time = val[kUtime_] + val[kCutime_] + val[kStime_] + val[kCstime_];
        float seconds = uptime - val[kStarttime_];
        cpuUsage_ = total_time / seconds;
    }
    else
    {
        cpuUsage_ = 0;
    }
}

void Process::determineUser() { user_ = LinuxParser::User(Pid()); }
void Process::determineCommand() { command_ = LinuxParser::Command(Pid()); }
void Process::determineRam(){
    string val = LinuxParser::Ram(Pid());
    //convert into MB
    try{
        long conv = std::stol(val) / 1000;
        ram_ = std::to_string(conv);
    }catch(const std::invalid_argument& arg){
        ram_ ="0";
    }
}

void Process::determineUptime(){
    uptime_ = LinuxParser::UpTime(Pid());
}