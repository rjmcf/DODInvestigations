add_library(
    Events
    "${CMAKE_CURRENT_SOURCE_DIR}/dummyEventListener.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/dummyEventListener.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/eventListener.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/eventManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/eventManager.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/timedEventFirer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/timedEventFirer.hpp"
)

target_include_directories(Events PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_definitions(Events PUBLIC)