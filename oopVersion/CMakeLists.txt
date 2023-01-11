add_library(
    OOPVersion
    "${CMAKE_CURRENT_SOURCE_DIR}/app.cpp"
)

if(PROFILING)
    target_link_libraries (OOPVersion PUBLIC TracyClient)
endif()