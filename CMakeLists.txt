cmake_minimum_required(VERSION 3.21)
project(fft_music_visualiser)

set(CMAKE_CXX_STANDARD 14)

add_executable(fft_music_visualiser main.cpp src/audio/AudioPlayer.h src/audio/AudioPlayer.cpp)

# Specify the path to the frameworks folder
set(SDL2_PATH "/frameworks")

# Find the SDL2 and SDL2 mixer frameworks
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Add the frameworks to your target
target_link_libraries(fft_music_visualiser PRIVATE
        "-F${SDL2_PATH}"
        "/Library/frameworks/SDL2.framework/SDL2"
        "/Library/frameworks/SDL2_mixer.framework/SDL2_mixer"
        )