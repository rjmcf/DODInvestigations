add_library(
    Geometry
    "${CMAKE_CURRENT_SOURCE_DIR}/point.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vector.hpp"
)

set_target_properties(Geometry PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Geometry PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")