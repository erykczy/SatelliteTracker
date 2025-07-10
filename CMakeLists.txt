cmake_minimum_required(VERSION 4.0.0)
project(SatelliteTracker)

add_executable(SatelliteTracker src/main.cpp)

add_subdirectory(extern/raylib)
add_subdirectory(extern/glm)
target_link_libraries(SatelliteTracker PRIVATE raylib glm::glm-header-only)
# target_include_directories(SatelliteTracker PRIVATE extern/raylib/src/external)