#!/bin/bash

mkdir -p ./build/ && cd ./build/
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release 
cmake --build ./ -j$(nproc)

echo -e "\e[1;35mBuild Finished at $(date) ✔✔ \e[0m"

