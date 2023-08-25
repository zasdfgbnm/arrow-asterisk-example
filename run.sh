#!/bin/bash

g++ --version
g++ -std=c++17 main.cpp -o main_gcc
./main_gcc
rm -f main_gcc

echo "---------------------"

clang++ --version
clang++ -std=c++17 main.cpp -o main_clang
./main_clang
rm -f main_clang

