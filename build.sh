#!/bin/bash
clear
mkdir -p build
cd build
cmake ..
cmake --build .
cd ..
./build/Editor/EditorMain
