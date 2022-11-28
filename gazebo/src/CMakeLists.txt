cmake_minimum_required(VERSION 3.15)

project(gaz VERSION 1.0)

set (gazebo_cmake_dir ${PROJECT_SOURCE_DIR}/cmake CACHE PATH "Location of CMake scripts")

set (GAZEBO_MAJOR_VERSION 11)
set (GAZEBO_MINOR_VERSION 12)
set (GAZEBO_PATCH_VERSION 0)
set (GAZEBO_VERSION ${GAZEBO_MAJOR_VERSION}.${GAZEBO_MINOR_VERSION})
set (GAZEBO_VERSION_FULL ${GAZEBO_MAJOR_VERSION}.${GAZEBO_MINOR_VERSION}.${GAZEBO_PATCH_VERSION})

set(GAZEBO_DEFAULT_MASTER_HOST localhost)
set(GAZEBO_DEFAULT_MASTER_PORT 11345)

set(GAZEBO_MODEL_DATABASE_URI http://models.gazebosim.org)

configure_file (${gazebo_cmake_dir}/gazebo_config.h.in ${PROJECT_BINARY_DIR}/gazebo/gazebo_config.h)

add_subdirectory(gazebo)

#add_executable(gaz)
#target_link_libraries(gaz gazmain)


