cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")

project(DODInvestigations)

set(OOP_VERSION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/oopVersion)

add_executable(${PROJECT_NAME} main.cpp app.cpp)

set(SDL2_DIR "./sdl/lib/cmake/SDL2/") 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${OOP_VERSION_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} Scene Enemies Animations Events)

add_subdirectory(${OOP_VERSION_DIR}/animations)
add_subdirectory(${OOP_VERSION_DIR}/enemies)
add_subdirectory(${OOP_VERSION_DIR}/events)
add_subdirectory(${OOP_VERSION_DIR}/scene)
