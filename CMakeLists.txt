 
cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME dominant_flow_finder)
project(${PROJ_NAME})
add_executable(
    ${PROJ_NAME} 
    src/main.cpp
)

set(CMAKE_CXX_FLAGS "-O3 -std=c++11")

include_directories(include)
find_package(PkgConfig REQUIRED)

pkg_check_modules(OpenCV REQUIRED opencv)
include_directories(${OpenCV_CFLAGS})
target_link_libraries(${PROJ_NAME} ${OpenCV_LDFLAGS})