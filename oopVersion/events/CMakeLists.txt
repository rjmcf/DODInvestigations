add_library(
    Events
    "${CMAKE_CURRENT_SOURCE_DIR}/dummyEventListener.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/eventManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/timedEventFirer.cpp"
)
