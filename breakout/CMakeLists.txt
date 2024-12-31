cmake_minimum_required(VERSION 3.15...3.31)
project(raylibtest VERSION 0.0.1
                  DESCRIPTION "cool"
                  LANGUAGES CXX)
add_executable(raylibtest main.cpp)
find_package(raylib CONFIG REQUIRED)
target_link_libraries(raylibtest PRIVATE raylib)
