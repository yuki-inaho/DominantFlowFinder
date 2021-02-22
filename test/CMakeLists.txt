cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(TestGraph test_graph.cpp)
target_link_libraries(TestGraph Graph GTest::GTest GTest::Main)
include_directories(${PROJECT_SOURCE_DIR}/include ${GTEST_INCLUDE_DIRS})

gtest_add_tests(TARGET TestGraph)