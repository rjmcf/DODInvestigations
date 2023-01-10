cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")

project(DODInvestigations)

add_subdirectory(oopVersion)

add_executable(${PROJECT_NAME} main.cpp app.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE OOPVersion)
