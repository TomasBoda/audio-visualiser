#ifndef FFT_MUSIC_VISUALISER_TIME_H
#define FFT_MUSIC_VISUALISER_TIME_H

#include <string>
#include <utility>

using time_pair = std::pair<int, int>;

time_pair seconds_to_minutes(int seconds);

std::string time_to_string(const time_pair & time);

#endif
