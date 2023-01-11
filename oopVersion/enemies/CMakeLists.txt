file(GLOB sources CONFIGURE_DEPENDS "*.cpp")
add_library(
    Enemies
    ${sources}
)

if(PROFILING)
    target_link_libraries (Enemies PUBLIC TracyClient)
endif()