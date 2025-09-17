cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 17)

project(Objetos CXX)

add_executable(Objetos
    src/main.cpp
    src/GameObject.cpp
    src/Component.cpp
    src/Scene.cpp
    src/Components/Transform.cpp
)

find_package(glm REQUIRED)

target_link_libraries(Objetos PRIVATE glm::glm)
target_include_directories(Objetos PRIVATE src)

