cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")

project(DODInvestigations)

set(OOP_VERSION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/oopVersion)

set(SHARED_INCLUDES
                ${OOP_VERSION_DIR}
                ${OOP_VERSION_DIR}/animations
                ${OOP_VERSION_DIR}/easing
                ${OOP_VERSION_DIR}/enemies
                ${OOP_VERSION_DIR}/events
                ${OOP_VERSION_DIR}/geometry
                ${OOP_VERSION_DIR}/interfaces
                ${OOP_VERSION_DIR}/scene
)

add_executable(${PROJECT_NAME} main.cpp app.cpp)

set(SDL2_DIR "./sdl/lib/cmake/SDL2/") 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SHARED_INCLUDES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} Scene Enemies Animations Interfaces Geometry Easing Events OOPVersion)

add_subdirectory(${OOP_VERSION_DIR})
add_subdirectory(${OOP_VERSION_DIR}/animations)
add_subdirectory(${OOP_VERSION_DIR}/easing)
add_subdirectory(${OOP_VERSION_DIR}/enemies)
add_subdirectory(${OOP_VERSION_DIR}/events)
add_subdirectory(${OOP_VERSION_DIR}/geometry)
add_subdirectory(${OOP_VERSION_DIR}/interfaces)
add_subdirectory(${OOP_VERSION_DIR}/scene)
