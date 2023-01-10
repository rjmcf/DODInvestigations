add_library(
    Enemies
    "${CMAKE_CURRENT_SOURCE_DIR}/enemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemy.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemyController.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemyController.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemyWithHealth.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemyWithHealth.hpp"
)

target_include_directories(Enemies PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_definitions(Enemies PUBLIC)

set(SDL2_DIR "../../sdl/lib/cmake/SDL2/") 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(Animations ${SDL2_LIBRARIES})