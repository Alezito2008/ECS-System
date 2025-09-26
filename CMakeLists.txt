cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 17)

project(Hydro CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(ECS)
add_subdirectory(Editor)
