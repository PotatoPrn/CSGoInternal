cmake_minimum_required(VERSION 3.26)
project(CsgoInternal)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_OUTPUT_PATH "../")
include_directories(include)

include_directories(Ext/imgui)
include_directories(Ext/imgui/backends)

include_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")
link_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86")

set (Utils
        src/Utils/MemUtils.cpp
        src/Utils/UiUtils.cpp
        src/Utils/HelperUtils.cpp
        src/Utils/HookUtil.cpp
        src/TraceRayUtil.cpp
)


set (D3D9Utils
        src/DX9Utils/DirectX.cpp
        src/DX9Utils/Draw.cpp
)

set (SDK
        include/Sdk/SDKFunctions.h
        src/Sdk/OffsetHunter.cpp
        src/Sdk/SDKFunctions.cpp
)


add_library(${PROJECT_NAME} SHARED
        main.cpp
        src/HackList.cpp
        src/MainThread.cpp


        ${Imgui}
        ${SDK}
        ${D3D9Utils}
        ${Utils}
)


