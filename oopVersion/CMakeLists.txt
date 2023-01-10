add_library(
    OOPVersion
    "${CMAKE_CURRENT_SOURCE_DIR}/colour.hpp"
)

set_target_properties(OOPVersion PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(OOPVersion PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")