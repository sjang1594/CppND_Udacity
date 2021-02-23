#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    string time = "00:00:00";
    long cal = 0;
    if (seconds > 0){
        // calculate hour
        cal = seconds / 3600;
        time = TimeValueToString(cal) + ":";
        // calculate min
        cal = (seconds / 60) % 60;
        time += TimeValueToString(cal) + ":";
        // calculate seconds
        cal = seconds % 60;
        time += TimeValueToString(cal);
    } 
    return time; 
}

std::string Format::TimeValueToString(long time){
    if(time < 10){
        return "0" + std::to_string(time);
    }
    else
    {
        return std::to_string(time);
    }
    

}