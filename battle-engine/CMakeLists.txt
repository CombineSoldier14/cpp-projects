cmake_minimum_required(VERSION 3.15...3.31)
project(BattleEngine VERSION 1.3.2
                  DESCRIPTION "A heavily customizable turn-based 1v1 battle game."
                  LANGUAGES CXX)
find_package(nlohmann_json CONFIG REQUIRED)
add_executable(BattleEngine main.cpp)
target_link_libraries(BattleEngine PRIVATE nlohmann_json::nlohmann_json)