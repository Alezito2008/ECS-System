cmake_minimum_required(VERSION 3.30)
project(Editor)

add_executable(EditorMain
    src/main.cpp
    src/Interface.cpp
)

target_include_directories(EditorMain PRIVATE ${PROJECT_SOURCE_DIR}/src)

# Librerias y demás

target_include_directories(EditorMain PRIVATE ${PROJECT_SOURCE_DIR}/../ECS/include)

target_link_libraries(EditorMain PRIVATE ECS)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/imgui)
target_link_libraries(EditorMain PRIVATE imgui)

find_package(OpenGL REQUIRED)
target_link_libraries(EditorMain PRIVATE OpenGL::GL)

find_package(glfw3 REQUIRED)
target_link_libraries(EditorMain PRIVATE glfw)
