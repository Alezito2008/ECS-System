#!/bin/bash
clear
mkdir -p build
cd build
cmake ..
cmake --build .
cd ..

# Si no existe compile_commands.json crear un symlink
if [ ! -f "compile_commands.json" ]; then
    ln -s ./build/compile_commands.json
fi

# Usando ./build.sh <ECS | Editor> se ejecuta el target 
TARGET="$1"
if [ "$TARGET" == "ECS" ]; then
    ./build/ECS/Test
elif [ "$TARGET" == "Editor" ]; then
    ./build/Editor/EditorMain
fi
