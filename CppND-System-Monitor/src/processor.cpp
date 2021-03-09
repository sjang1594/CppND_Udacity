#include "processor.h"
#include "linux_parser.h"

//Define constructor again for processor & assign to default values, 0.
Processor::Processor() : prevTotalCpuTime(0.0), prevIdleCpuTime(0.0){};

// TODO: Return the aggregate CPU utilizations
float Processor::Utilization() {
    std::vector<long> cpuVal = convertToLong(LinuxParser::CpuUtilization());

    // Add all float values in order to calculate the total cpu times after boot up.
    float totalCpuTime =
        cpuVal[LinuxParser::kUser_] + cpuVal[LinuxParser::kNice_] + 
        cpuVal[LinuxParser::kSystem_] + cpuVal[LinuxParser::kIdle_] +
        cpuVal[LinuxParser::kIOwait_] + cpuVal[LinuxParser::kIRQ_] + 
        cpuVal[LinuxParser::kSoftIRQ_] + cpuVal[LinuxParser::kSteal_];

    // The CPU is idle when it's requesting IO handle comes in.
    float idleTime = cpuVal[LinuxParser::kIdle_] + cpuVal[LinuxParser::kIOwait_];

    // After updating, calculate the cpu usage
    float newCpuIdle = idleTime - prevIdleCpuTime;
    float newCpuTotal = totalCpuTime - prevTotalCpuTime;
    // average out the new or current cpu usage.
    float newCpuUsage = (newCpuTotal - newCpuIdle) / newCpuTotal;

    // then apply & update the cputime and idletime
    prevIdleCpuTime = idleTime;
    prevTotalCpuTime = totalCpuTime;
    return newCpuUsage;
}

std::vector<long> Processor::convertToLong(std::vector<std::string> val){
    std::vector<long> convertedValues{};

    for(int it =0; it < (int)val.size(); it++){
        try{
            convertedValues.push_back(std::stoi(val[it]));
        } catch(const std::invalid_argument& arg){
            convertedValues.push_back((long)0);
        }
    }

    return convertedValues;
}