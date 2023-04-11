#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

if [ ! -d "linux" ]; then
    echo ">> Build folder not found, creating the build folder..."
    mkdir linux
    echo ">> Build folder created"
fi

cd macos

echo "The build script for Linux is not implemented yet..."