cmake_minimum_required(VERSION 3.26)
project(CsgoInternal)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_OUTPUT_PATH "../")
include_directories(include)

include_directories(Ext/imgui)

include_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")
link_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86")


add_library(${PROJECT_NAME} SHARED main.cpp
        src/MemUtils.cpp
        src/UiUtils.cpp
        src/HackList.cpp
        src/HelperUtils.cpp
        include/SDKFunctions.h
        src/GuiLib.cpp
        src/OffsetHunter.cpp
        src/HookUtil.cpp
        src/DirectX.cpp

        Ext/imgui/imgui.cpp
        Ext/imgui/imgui_draw.cpp
        Ext/imgui/imgui_tables.cpp
        Ext/imgui/imgui_widgets.cpp
        src/Draw.cpp
        include/Draw.h
        src/MainThread.cpp
        include/MainThread.h


)


