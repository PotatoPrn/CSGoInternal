cmake_minimum_required(VERSION 3.26)
project(IntTemplate)

set(CMAKE_CXX_STANDARD 20)

set(LIBRARY_OUTPUT_PATH "../")
include_directories(include)

add_library(${PROJECT_NAME} SHARED main.cpp
        src/MemUtils.cpp
        src/UiUtils.cpp
        src/HookUtil.cpp
        include/HookUtil.h)