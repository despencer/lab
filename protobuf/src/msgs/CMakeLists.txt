add_executable(gazebomsgs_out generator/GazeboGenerator.cc generator/gazebo_generator.cc)
target_include_directories(gazebomsgs_out PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gazebomsgs_out ${PROTOBUF_LIBRARY} ${PROTOBUF_PROTOC_LIBRARY})

set(msgs color.proto)

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
add_library(gazebo_msgs OBJECT ${PROTO_SRCS})

