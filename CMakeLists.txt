cmake_minimum_required(VERSION 3.21)
project(fft_music_visualiser)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/SDL)
include_directories(libs/SDL/include)

add_subdirectory(libs/fftw3)
include_directories(libs/fftw3/api)

set(wxWidgets_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/wxWidgets)
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

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

target_link_libraries(fft_music_visualiser PRIVATE SDL2 fftw3 ${wxWidgets_LIBRARIES})