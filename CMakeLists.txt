cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(SDL2_DIR "./sdl/lib/cmake/SDL2/") 

project(DODInvestigations)

add_subdirectory(oopVersion)
add_subdirectory(oopVersion/animations)
add_subdirectory(oopVersion/easing)
add_subdirectory(oopVersion/enemies)
add_subdirectory(oopVersion/events)
add_subdirectory(oopVersion/geometry)
add_subdirectory(oopVersion/interfaces)
add_subdirectory(oopVersion/scene)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp app.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} OOPVersion Easing  Geometry Interfaces Scene Enemies Animations Events)
