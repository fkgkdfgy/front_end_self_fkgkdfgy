project(front_end_self)
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_BUILD_TYPE "Debug")
cmake_minimum_required(VERSION 3.1)

include(./cmake/opencv.cmake)

find_package(Threads)

include_directories(core/include)

add_executable(main app/main.cpp )
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})