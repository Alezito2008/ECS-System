#!/bin/bash
clear
mkdir -p build
cd build
cmake ..
cmake --build .

BUILD_STATUS=$?

cd ..

# Si no existe compile_commands.json crear un symlink
if [ ! -f "compile_commands.json" ]; then
    ln -s ./build/compile_commands.json
fi

if [ $BUILD_STATUS -ne 0 ]; then
    exit
fi

# Usando ./build.sh <ECS | Editor> se ejecuta el target 
TARGET="$1"
if [ "$TARGET" == "ECS" ]; then
    ./build/ECS/Test
elif [ "$TARGET" == "Editor" ]; then
    ./build/Editor/EditorMain
fi
