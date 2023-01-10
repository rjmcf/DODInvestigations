add_library(
    Scene
    "${CMAKE_CURRENT_SOURCE_DIR}/scene.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/scene.cpp"
)

target_include_directories(Scene PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_definitions(Scene PUBLIC)