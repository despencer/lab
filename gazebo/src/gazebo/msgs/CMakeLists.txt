add_executable(gazebomsgs_out generator/GazeboGenerator.cc generator/gazebo_generator.cc)
target_include_directories(gazebomsgs_out PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR})
target_link_libraries(gazebomsgs_out ${PROTOBUF_LIBRARY} ${PROTOBUF_PROTOC_LIBRARY})

set(msgs
 any.proto
 axis.proto
 battery.proto
 boxgeom.proto
 camerasensor.proto
 collision.proto
 color.proto
 contactsensor.proto
 cylindergeom.proto
 density.proto
 distortion.proto
 fog.proto
 friction.proto
 header.proto
 heightmapgeom.proto
 geometry.proto
 gps_sensor.proto
 gui.proto
 gui_camera.proto
 gz_string.proto
 gz_string_v.proto
 image.proto
 imagegeom.proto
 imu_sensor.proto
 inertial.proto
 joint.proto
 light.proto
 link.proto
 log_control.proto
 log_status.proto
 logical_camera_sensor.proto
 material.proto
 meshgeom.proto
 model.proto
 packet.proto
 plugin.proto
 planegeom.proto
 polylinegeom.proto
 pose.proto
 projector.proto
 publish.proto
 publishers.proto
 quaternion.proto
 raysensor.proto
 request.proto
 response.proto
 scene.proto
 sensor.proto
 sensor_noise.proto
 sky.proto
 spheregeom.proto
 spherical_coordinates.proto
 subscribe.proto
 surface.proto
 track_visual.proto
 time.proto
 vector2d.proto
 vector3d.proto
 visual.proto)

set(
  GAZEBOMSGS_OUT_EXECUTABLE
  "$<TARGET_FILE:gazebomsgs_out>"
  CACHE STRING
  "gazebomsgs_out executable used in gazebo protobuf msgs generation.")

set(PROTO_SRCS)
set(PROTO_HDRS)
foreach(FIL ${msgs})
  get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
  get_filename_component(FIL_WE ${FIL} NAME_WE)

  list(APPEND PROTO_SRCS "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc")
  list(APPEND PROTO_HDRS "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h")

  add_custom_command(
    OUTPUT
      "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc"
      "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h"
    COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS --plugin=protoc-gen-gazebomsgs=${GAZEBOMSGS_OUT_EXECUTABLE} --cpp_out=dllexport_decl=GZ_MSGS_VISIBLE:${CMAKE_CURRENT_BINARY_DIR} --gazebomsgs_out=${CMAKE_CURRENT_BINARY_DIR} --proto_path=${CMAKE_CURRENT_SOURCE_DIR} ${ABS_FIL}
    DEPENDS ${ABS_FIL} gazebomsgs_out
    COMMENT "Running C++ protocol buffer compiler on ${FIL}"
    VERBATIM )
endforeach()

set_source_files_properties(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)
add_library(gazebo_msgs OBJECT ${PROTO_SRCS} MsgFactory.cc msgs.cc)
target_include_directories(gazebo_msgs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR}
   ${ignition-math6_INCLUDE_DIRS} ${SDFormat_INCLUDE_DIRS} ${ignition-msgs5_INCLUDE_DIRS})
add_dependencies(gazebo_msgs gazebomsgs_out)

set (message_headers "")

foreach (hdr ${PROTO_HDRS})
  string (REPLACE "${CMAKE_CURRENT_BINARY_DIR}/" "" hdr ${hdr})
  set (message_headers "${message_headers}#include \"${hdr}\"\n")
endforeach()

configure_file (${PROJECT_SOURCE_DIR}/gazebo/msgs/MessageTypes.hh.in
                ${CMAKE_CURRENT_BINARY_DIR}/MessageTypes.hh )




