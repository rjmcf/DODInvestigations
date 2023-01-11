file(GLOB sources CONFIGURE_DEPENDS "*.cpp")
add_library(
    Animations
    ${sources}
)

if(PROFILING)
    target_link_libraries (Animations PUBLIC TracyClient)
endif()