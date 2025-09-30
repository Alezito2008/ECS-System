cmake_minimum_required(VERSION 3.30)

project(Editor)

add_executable(EditorMain
    src/main.cpp
    src/Interface.cpp
    src/DockLayout.cpp
    src/Themes.cpp
    src/Preferences.cpp
    src/Panels/Console/Console.cpp
    src/Panels/Tree/Tree.cpp
    src/Panels/MenuBar/MenuBar.cpp
    src/Panels/Inspector/Inspector.cpp
)

target_include_directories(EditorMain PRIVATE
    external/include
    src/include
    src/Panels
)

# Librerias y demás

target_include_directories(EditorMain PRIVATE ${PROJECT_SOURCE_DIR}/../ECS/include)

target_link_libraries(EditorMain PRIVATE ECS)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/imgui)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(EditorMain PRIVATE
    OpenGL::GL
    glfw
    imgui
)
