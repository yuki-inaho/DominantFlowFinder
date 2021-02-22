 
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME dominant_flow_finder)
project(${PROJ_NAME})
add_executable(
    ${PROJ_NAME} 
    src/main.cpp 
    src/Graph.cpp
    src/PixelNode.cpp
    src/convert.cpp
)

#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "-O0 -std=c++11")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-Ofast -std=c++11")

include_directories(include)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(OpenCV REQUIRED opencv)
include_directories(${OpenCV_CFLAGS})
target_link_libraries(${PROJ_NAME} ${OpenCV_LDFLAGS})
target_link_libraries(${PROJ_NAME} stdc++fs)

set(BUILD_TEST FALSE)
if(BUILD_TEST)
    add_subdirectory(test)
    add_library(
        Graph STATIC
        src/Graph.cpp
        src/PixelNode.cpp
        src/convert.cpp
    )
    target_link_libraries(Graph ${OpenCV_LDFLAGS})
endif()