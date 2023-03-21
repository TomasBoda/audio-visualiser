cmake_minimum_required(VERSION 3.21)
project(fft_music_visualiser)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libraries/SDL2)

add_subdirectory(libraries/fftw3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/fftw3/api)

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})

add_executable(fft_music_visualiser
        main.cpp
        src/audio/AudioPlayer.h
        src/audio/AudioPlayer.cpp
        src/app/App.h
        src/config.h
        src/config.cpp
        src/utils/FFT.h
        src/gui/Window.h src/gui/Window.cpp)

target_link_libraries(fft_music_visualiser PRIVATE SDL2 ${wxWidgets_LIBRARIES} fftw3)