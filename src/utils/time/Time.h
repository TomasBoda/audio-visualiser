#ifndef FFT_MUSIC_VISUALISER_TIME_H
#define FFT_MUSIC_VISUALISER_TIME_H

#include <string>
#include <utility>

using time_pair = std::pair<int, int>;

/*
 * Convert seconds to minutes and seconds
 * This method converts seconds into the corresponding number of minutes and seconds
 * @param seconds number of seconds
 */
time_pair seconds_to_minutes(int seconds);

/*
 * Convert timestamp to string
 * This method converts a timestamp into a formatted string
 * @param time pair representing minutes and seconds
 */
std::string time_to_string(const time_pair & time);

#endif
