#!/bin/bash

# clean all project file
rm -rf arcade
rm -rf ./lib/*.so
rm -rf build
rm -rf saves

# clean all tmp file
rm -rf ./**/*.o
rm -rf ./**/*.vgcore
rm -rf ./**/*.so
rm -rf ./**/*.out
rm -rf ./**/*.gcno
rm -rf ./**/*.gcda
rm -rf vgcore.*

echo -e "\e[1;35mClean Finished at $(date) ✔✔ \e[0m"
