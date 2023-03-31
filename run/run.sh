#!/bin/bash

bash ./run/install.sh
bash ./run/build.sh

echo ">> Running the application..."
./build/fft_music_visualiser
echo ">> Application exited"