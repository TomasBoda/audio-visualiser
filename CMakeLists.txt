cmake_minimum_required(VERSION 3.21)

if (UNIX)
    enable_language(OBJCXX)
endif (UNIX)

project(fft_music_visualiser LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

message(STATUS ">> Adding SDL library to the build path...")
add_subdirectory(libs/SDL)
include_directories(libs/SDL/include)
message(STATUS ">> SDL added")

message(STATUS ">> Adding FFTW3 library to the build path...")
add_subdirectory(libs/fftw3)
include_directories(libs/fftw3/api)
message(STATUS ">> FFTW3 added")

message(STATUS ">> Adding wxWidgets library to the build path...")
add_subdirectory(libs/wxWidgets)
include_directories(libs/wxWidgets/include)
message(STATUS ">> wxWidgets added")

add_executable(fft_music_visualiser
        main.cpp
        src/audio/AudioPlayer.h
        src/audio/AudioPlayer.cpp
        src/app/App.h
        src/config/config.h
        src/config/config.cpp
        src/gui/window/Window.h
        src/utils/dialog/Dialog.h
        src/app/App.cpp
        src/utils/audio/Audio.h
        src/utils/visualiser/Visualiser.h
        src/gui/visualisers/equalizer/Equalizer.h
        src/gui/visualisers/circular/Circular.h
        src/utils/frame/Frame.h src/utils/frame/Frame.cpp src/gui/window/Window.cpp src/gui/visualisers/equalizer/Equalizer.cpp src/gui/visualisers/circular/Circular.cpp src/utils/observer/Observer.h src/utils/audio/Audio.cpp src/utils/observer/Observer.cpp src/utils/dialog/Dialog.cpp src/utils/visualiser/Visualiser.cpp src/gui/visualisers/volumes/Volumes.h src/gui/visualisers/volumes/Volumes.cpp)

target_link_libraries(fft_music_visualiser PRIVATE SDL2 fftw3 wx::net wx::core wx::base)