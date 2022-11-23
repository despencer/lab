add_subdirectory(common)

include(FindBoost)
find_package(Boost REQUIRED filesystem)

add_executable(gazmain main.cc)
target_link_libraries(gazmain common ${Boost_LIBRARIES})
target_include_directories(gazmain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_LIBRARY_DIR})



