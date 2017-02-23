cmake_minimum_required(VERSION 2.8)
project (RudyEngine)

add_subdirectory(Engine)

add_executable(test main.cpp)
target_link_libraries(test engine)