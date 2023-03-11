cmake_minimum_required(VERSION 3.21)
project(fft_music_visualiser)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_PATH "/frameworks")

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(wxWidgets_ROOT_DIR /Library/frameworks/wxWidgets)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(fft_music_visualiser main.cpp src/audio/AudioPlayer.h src/audio/AudioPlayer.cpp src/app/App.h src/window/Window.h src/config.h src/config.cpp)

# Add the frameworks to your target
target_link_libraries(fft_music_visualiser PRIVATE
        "/Library/${SDL2_PATH}"
        "/Library/frameworks/SDL2.framework/SDL2"
        "/Library/frameworks/SDL2_mixer.framework/SDL2_mixer"
        ${wxWidgets_LIBRARIES}
        )