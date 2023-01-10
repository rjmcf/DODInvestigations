add_library(
    Animations
    "${CMAKE_CURRENT_SOURCE_DIR}/animatedInterface.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animation.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animationChain.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animationChain.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animationColour.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animationController.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animationController.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animationDeform.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animationHealth.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animationTranslate.hpp"
)

set(SDL2_DIR "../../sdl/lib/cmake/SDL2/") 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(Animations ${SDL2_LIBRARIES})

target_include_directories(Animations PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_definitions(Animations PUBLIC)

