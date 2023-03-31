#!/bin/bash

echo ">> Checking operating system..."

# Check operating system
if [[ "$OSTYPE" == "darwin"* ]]; then
  # macOS
  echo ">> Operating system is macOS"
  brew --version >/dev/null 2>&1 || /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
elif [[ "$OSTYPE" == "msys"* ]]; then
  # Windows
  echo ">> Operating system is Windows"
  echo ">> Windows is not currently supported."
  exit 1
else
  # Linux
  echo ">> Operating system is Linux"
  echo ">> Updating package manager..."
  sudo apt-get update && sudo apt-get -y upgrade
  echo ">> Package manager updated"
fi

# Check if gcc is installed
echo ">> Checking for gcc installation..."
if ! command -v gcc &> /dev/null; then
  echo ">> gcc is not installed, installing now..."

  if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    brew install gcc
  elif [[ "$OSTYPE" == "msys"* ]]; then
    # Windows
    echo ">> Windows is not currently supported."
    exit 1
  else
    # Linux
    sudo apt-get -y install gcc
  fi
  echo ">> gcc installed successfully"
else
  echo ">> gcc is installed"
fi

# Check if cmake is installed
echo ">> Checking for cmake installation..."
if ! command -v cmake &> /dev/null; then
  echo "cmake is not installed. Installing now..."

  if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    brew install cmake
  elif [[ "$OSTYPE" == "msys"* ]]; then
    # Windows
    echo ">> Windows is not currently supported"
    exit 1
  else
    # Linux
    sudo apt-get -y install cmake
  fi

  echo ">> cmake installed successfully"
else
  echo ">> cmake is installed"
fi