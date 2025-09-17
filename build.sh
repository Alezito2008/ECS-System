#!/bin/bash
clear
mkdir -p build
cd build
cmake ..
cmake --build .
./Objetos
