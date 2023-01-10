file(GLOB sources CONFIGURE_DEPENDS "*.cpp")
add_library(
    Enemies
    ${sources}
)
