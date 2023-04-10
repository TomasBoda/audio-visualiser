#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

if [ ! -d "macos" ]; then
    echo ">> Build folder not found, creating the build folder..."
    mkdir macos
    echo ">> Build folder created"
fi

cd macos

if [ ! -f "Makefile" ]; then
    echo ">> Makefile not found, generating CMake files..."
    cmake ../..
    echo ">> CMake files generated"
fi

echo ">> Building the application..."
make
echo ">> Application built"

echo ">> Running the application..."
./fft_music_visualiser
echo ">> Application exited"