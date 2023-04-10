# Music Visualizer
by Tomáš Boďa

## About
A cross-platform application written in C++ that visualizes audio in real-time using frequency spectrum analyzers and the FFT algorithm.

The project uses the following external libraries:
1. `wxWidgets` for cross-platform window and GUI
2. `SDL2` for cross-platform audio processing and playback
3. `FFTW3` for Fast Fourier Transform calculations to analyze frequency spectrum

## Setup and build
The following section demonstrates the installation, setup and build of the project.

1. Make sure you have C++ compiler, CMake and Make installed on your computer and added to `PATH` variable
2. Clone the project with all its submodules using `git clone --recurse-submodules -j8 https://gitlab.mff.cuni.cz/bodat/music-visualiser.git`
3. Navigate to the project root using `cd music-visualiser`
4. Depending on your platform, build the application using one of the prepared build scripts:
   1. on Windows, open Git Bash and run `./run/windows.sh`
   2. on MacOS, open terminal and run `./run/macos.sh`
   3. on Linux, open terminal and run `./run/linux.sh`
5. After the build is complete, the application will start automatically