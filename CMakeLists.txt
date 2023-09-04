cmake_minimum_required(VERSION 3.26)
project(CsgoInternal)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_OUTPUT_PATH "../")
include_directories(include)

include_directories(Ext/imgui)

add_library(${PROJECT_NAME} SHARED main.cpp
        src/MemUtils.cpp
        src/UiUtils.cpp
        src/HackList.cpp
        src/HelperUtils.cpp
        include/SDKFunctions.h
        src/GuiLib.cpp


        Ext/imgui/imgui.cpp
        Ext/imgui/imgui_draw.cpp
        Ext/imgui/imgui_tables.cpp
        Ext/imgui/imgui_widgets.cpp
        src/OffsetHunter.cpp

)


