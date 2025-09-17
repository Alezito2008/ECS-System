cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 17)

project(ECS CXX)

add_library(ECS STATIC
    src/GameObject.cpp
    src/Component.cpp
    src/Scene.cpp
    src/Components/Transform.cpp
)

target_include_directories(ECS
PUBLIC ${PROJECT_SOURCE_DIR}/include/ECS
PRIVATE ${PROJECT_SOURCE_DIR}/private
)

find_package(glm REQUIRED)
target_link_libraries(ECS PRIVATE glm::glm)

# EJecutable para probar cosas

add_executable(Objetos src/main.cpp)
target_link_libraries(Objetos PRIVATE ECS)

target_include_directories(Objetos
PUBLIC ${PROJECT_SOURCE_DIR}/include/ECS
PRIVATE ${PROJECT_SOURCE_DIR}/private
)
