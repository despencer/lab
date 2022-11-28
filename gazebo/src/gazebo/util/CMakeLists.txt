add_library(gazebo_util OBJECT LogRecord.cc)
target_include_directories(gazebo_util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR}
    ${SDFormat_INCLUDE_DIRS} ${ignition-common3_INCLUDE_DIRS} ${ignition-msgs5_INCLUDE_DIRS})
