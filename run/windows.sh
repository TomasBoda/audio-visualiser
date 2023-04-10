#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

if [ ! -d "windows" ]; then
    echo ">> Build folder not found, creating the build folder..."
    mkdir windows
    echo ">> Build folder created"
fi

cd windows

if [ ! -f "Makefile" ]; then
    echo ">> Makefile not found, generating CMake files..."
    cmake ../.. -G "MinGW Makefiles" -D wxBUILD_PRECOMP:BOOL=OFF -DCMAKE_EXE_LINKER_FLAGS="-static-libgcc -static-libstdc++" -DCMAKE_FIND_LIBRARY_SUFFIXES=".a"
    echo ">> CMake files generated"
fi

echo ">> Building the application..."
mingw32-Makefile
echo ">> Application built"

echo ">> Binding libraries to the executable..."
mv ./libs/fftw3/libfftw3.dll .
mv ./libs/SDL/SDL2d.dll .
mv ./libs/wxWidgets/lib/gcc_x64_dll/wxmsw330ud_core_gcc_custom.dll .
mv ./libs/wxWidgets/lib/gcc_x64_dll/wxbase330ud_gcc_custom.dll .
echo ">> Done"

echo ">> Running the application..."
./fft_music_visualiser.exe
echo ">> Application exited"