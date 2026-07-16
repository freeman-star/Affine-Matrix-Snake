cmake_minimum_required(VERSION 3.10)
project(SnakeGame
    VERSION 1.0
    DESCRIPTION "A simple snake game"
    LANGUAGES CXX
)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable Qt meta-object compilation and UI/Resource handling
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/msys64/ucrt64")

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
add_executable(SnakeGame WIN32 
    src/main.cpp 
    src/Snake.cpp 
    src/Snake.h
)

target_link_libraries(SnakeGame PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)