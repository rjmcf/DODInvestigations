add_library(
    Easing
    "${CMAKE_CURRENT_SOURCE_DIR}/easingFunction.hpp"
)

set_target_properties(Easing PROPERTIES LINKER_LANGUAGE CXX)
