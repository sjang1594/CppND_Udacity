#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

class Processor {
 public:
  //constructor
  Processor();
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    float prevTotalCpuTime;
    float prevIdleCpuTime;

    std::vector<long> convertToLong(std::vector<std::string> values);
};


#endif