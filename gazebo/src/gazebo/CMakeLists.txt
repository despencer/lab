include(FindBoost)
find_package(Boost REQUIRED filesystem thread iostreams)
find_package(sdformat9 REQUIRED)
find_package(ignition-common3 REQUIRED)
find_package(ignition-msgs5 REQUIRED)
find_package(ignition-math6 REQUIRED)
find_package(ignition-fuel_tools4 REQUIRED)
find_package(Protobuf REQUIRED)
find_package(CURL)
pkg_check_modules(TBB tbb)
pkg_check_modules(tinyxml tinyxml)

add_subdirectory(msgs)
add_subdirectory(common)
add_subdirectory(transport)
add_subdirectory(util)

add_dependencies(gazebo_common gazebo_msgs)
add_dependencies(gazebo_util gazebo_msgs)

add_executable(gazmain main.cc Master.cc)
target_link_libraries(gazmain gazebo_msgs gazebo_common gazebo_util gazebo_transport ${Boost_LIBRARIES} ${Protobuf_LIBRARIES} ${SDFormat_LIBRARIES}
   ${TBB_LIBRARIES} ${tinyxml_LIBRARIES} ${ignition-common3_LIBRARIES} ${ignition-msgs5_LIBRARIES} ${ignition-fuel_tools4_LIBRARIES} 
   ${CURL_LIBRARIES} freeimage tar)


target_include_directories(gazmain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_LIBRARY_DIR} ${SDFormat_INCLUDE_DIRS})



