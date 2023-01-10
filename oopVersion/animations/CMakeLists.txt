file(GLOB sources CONFIGURE_DEPENDS "*.cpp")
add_library(
    Animations
    ${sources}
)
