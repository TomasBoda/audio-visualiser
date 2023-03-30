cmake_minimum_required(VERSION 3.21)

enable_language(OBJCXX)
project(fft_music_visualiser LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/SDL)
include_directories(libs/SDL/include)

add_subdirectory(libs/fftw3)
include_directories(libs/fftw3/api)

add_subdirectory(libs/wxWidgets)

add_executable(fft_music_visualiser
        main.cpp
        src/audio/AudioPlayer.h
        src/audio/AudioPlayer.cpp
        src/app/App.h
        src/config/config.h
        src/config/config.cpp
        src/gui/Window.h
        src/utils/Dialog.h
        src/app/App.cpp
        src/utils/Audio.h
        src/utils/Visualiser.h
        src/gui/visualisers/Equalizer.h
        src/gui/visualisers/Circular.h
        src/utils/Frame.h)

target_link_libraries(fft_music_visualiser PRIVATE SDL2 fftw3 wx::net wx::core wx::base)