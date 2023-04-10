# Music Visualizer
by Tomáš Boďa

![Music Visualiser](music-visualiser.gif)

## About
A cross-platform application written in C++ that visualizes audio in real-time using frequency spectrum analyzers and the FFT algorithm.

The project utilizes the following external libraries:
1. `wxWidgets` for cross-platform window and GUI
2. `SDL2` for cross-platform audio processing and playback
3. `FFTW3` for Fast Fourier Transform calculations to analyze frequency spectrum

## Requirements
For building and running the application, you will need the following installed on your system.

- C++ compiler (tested using `MinGW` compiler)
- CMake build tool (tested using `cmake` version `3.26.2`)
- Make (tested using `make` version `GNU make 3.8.1`) - usually comes with the `MinGW` compiler

All mentioned tools need to be added to the system `PATH`. The prepared build scripts use `gcc`, `cmake` and `mingw32-make` commands to build and run the application.

If you want to build the application with these tools installed elsewhere on your system, edit the `/run/macos.sh`, `/run/windows.sh`, `/run/linux.sh` scripts to use the tools from other locations on your system.

## Setup and build
The following section demonstrates the installation, setup and build of the project.

1. Clone the project with all its submodules using `git clone --recurse-submodules -j8 https://gitlab.mff.cuni.cz/bodat/music-visualiser.git`
2. Navigate to the project root using `cd music-visualiser`
3. Depending on your platform, build the application using one of the prepared build scripts:
   1. on Windows, open Git Bash and run `./run/windows.sh`
   2. on MacOS, open terminal and run `./run/macos.sh`
   3. on Linux, open terminal and run `./run/linux.sh`
4. After the build is complete, the application will start automatically
