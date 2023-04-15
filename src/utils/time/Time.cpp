#include "Time.h"

time_pair seconds_to_minutes(int seconds) {
    return time_pair(seconds / 60, seconds % 60);
}

std::string time_to_string(const time_pair & time) {
    std::string seconds_string = (time.first < 10 ? "0" : "") + std::to_string(time.first);
    std::string minutes_string = (time.second < 10 ? "0" : "") + std::to_string(time.second);
    return seconds_string + ":" + minutes_string;
}