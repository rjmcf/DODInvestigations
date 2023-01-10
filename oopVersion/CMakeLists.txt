add_library(
    OOPVersion
    "${CMAKE_CURRENT_SOURCE_DIR}/testOOP.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/testOOP.cpp"
)

target_include_directories(OOPVersion PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_definitions(OOPVersion PRIVATE)