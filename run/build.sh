#!/bin/bash

if [ ! -d "build" ]; then
  echo ">> Build folder not found, creating the build folder..."
  mkdir build
  echo ">> Build folder created"
fi

cd build

if [ ! -f "Makefile" ]; then
  echo ">> Makefile not found, generating CMake files..."
  cmake ..
  echo ">> CMake files generated"
fi

echo ">> Building the application..."
make
echo ">> Application built"