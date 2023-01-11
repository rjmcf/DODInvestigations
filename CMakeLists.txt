cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")

option(PROFILING "If ON, adds Tracy profiler" ON)
if(PROFILING)
    include(FetchContent)
    FetchContent_Declare(
        tracy
        GIT_REPOSITORY https://github.com/wolfpld/tracy.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(tracy)
endif()

project(DODInvestigations)

set(OOP_VERSION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/oopVersion)

add_executable(${PROJECT_NAME} main.cpp)

set(SDL2_DIR "./sdl/lib/cmake/SDL2/") 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${OOP_VERSION_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} OOPVersion Scene Enemies Animations Events)

if(PROFILING)
    target_link_libraries (${PROJECT_NAME} PUBLIC TracyClient )
endif()


add_subdirectory(${OOP_VERSION_DIR})
add_subdirectory(${OOP_VERSION_DIR}/animations)
add_subdirectory(${OOP_VERSION_DIR}/enemies)
add_subdirectory(${OOP_VERSION_DIR}/events)
add_subdirectory(${OOP_VERSION_DIR}/scene)

# Usage: cmake -S .. -G "MinGW Makefiles" --preset=default