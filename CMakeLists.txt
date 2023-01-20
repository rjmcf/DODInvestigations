# Preamble
cmake_minimum_required(VERSION 3.25.1)
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")

# Handy for debugging
macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()
# Usage: print_all_variables()

# Get Tracy
option(PROFILING "If ON, adds Tracy profiler" ON)
if(PROFILING)
    include(FetchContent)
    FetchContent_Declare(
        tracy
        GIT_REPOSITORY https://github.com/wolfpld/tracy.git
        GIT_TAG v0.9
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(tracy)
    include_directories(${tracy_SOURCE_DIR}/public/tracy)
endif()

# Set up project
project(DODInvestigations)
add_executable(${PROJECT_NAME} main.cpp)

# Set implementation version
set(IMPL_VERSION OOP)

if (IMPL_VERSION STREQUAL OOP)
    set(USING_OOP 1)
endif()

# Configure header to pull variables from here into code
configure_file(programConfig.h.in programConfig.h)
include_directories("${PROJECT_BINARY_DIR}")

# Set up SDL2
set(SDL2_DIR "./sdl/lib/cmake/SDL2/") 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# Compile correct implementation version
if (IMPL_VERSION STREQUAL OOP)
    # Set up OOP subdirectories (Note: only need ones that contain .cpp files)
    set(OOP_VERSION_DIR ${CMAKE_SOURCE_DIR}/oopVersion)
    include_directories(${OOP_VERSION_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE OOPVersion Scene Enemies Animations AnimationLibrary Events Attachments Utils)
    add_subdirectory(${OOP_VERSION_DIR})
    add_subdirectory(${OOP_VERSION_DIR}/animations)
    add_subdirectory(${OOP_VERSION_DIR}/animations/animationLibrary)
    add_subdirectory(${OOP_VERSION_DIR}/enemies)
    add_subdirectory(${OOP_VERSION_DIR}/enemies/attachments)
    add_subdirectory(${OOP_VERSION_DIR}/events)
    add_subdirectory(${OOP_VERSION_DIR}/scene)
    add_subdirectory(${OOP_VERSION_DIR}/utils)
endif()


# Usage: cmake -S .. -G "MinGW Makefiles" --preset=default