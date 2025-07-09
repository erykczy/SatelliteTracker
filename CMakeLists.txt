cmake_minimum_required(VERSION 4.0.0)
project(SatelliteTracker)

add_executable(SatelliteTracker src/main.cpp)

add_subdirectory(extern/raylib)
target_link_libraries(SatelliteTracker PRIVATE raylib)