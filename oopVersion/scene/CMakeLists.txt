add_library(
    Scene
    "${CMAKE_CURRENT_SOURCE_DIR}/scene.cpp"
)

if(PROFILING)
    target_link_libraries (Scene PUBLIC TracyClient)
endif()