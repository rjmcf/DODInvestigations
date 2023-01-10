add_library(
    Interfaces
    "${CMAKE_CURRENT_SOURCE_DIR}/colourHaverInterface.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/healthHaverInterface.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/rectHaverInterface.hpp"
)

set_target_properties(Interfaces PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Interfaces PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
