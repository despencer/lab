cmake_minimum_required(VERSION 3.15)

project(TbbTest VERSION 1.0)

# find_package(TBB 2021.5.0 REQUIRED)
include(FindPkgConfig)
pkg_check_modules(TBB tbb)
link_directories(${TBB_LIBRARY_DIR})

add_executable(tbbtest tbbtest.cc Master.cc Connection.cc)

target_link_libraries(tbbtest PRIVATE ${TBB_LIBRARIES})
