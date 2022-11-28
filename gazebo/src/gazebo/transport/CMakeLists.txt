add_library(gazebo_transport OBJECT
  CallbackHelper.cc
  Connection.cc
  ConnectionManager.cc
  IOManager.cc
  Node.cc
  Publication.cc
  PublicationTransport.cc
  Publisher.cc
  Subscriber.cc
  SubscriptionTransport.cc
  TopicManager.cc
  TransportIface.cc)

target_include_directories(gazebo_transport PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR} ${SDFormat_INCLUDE_DIRS}
      ${ignition-common3_INCLUDE_DIRS} ${ignition-msgs5_INCLUDE_DIRS})

set_property(
  SOURCE TransportIface.cc
  PROPERTY COMPILE_DEFINITIONS
  GAZEBO_DEFAULT_MASTER_HOST="${GAZEBO_DEFAULT_MASTER_HOST}"
  GAZEBO_DEFAULT_MASTER_PORT=${GAZEBO_DEFAULT_MASTER_PORT}
)

set (headers
  CallbackHelper.hh
  Connection.hh
  ConnectionManager.hh
  IOManager.hh
  Node.hh
  Publication.hh
  Publisher.hh
  PublicationTransport.hh
  SubscribeOptions.hh
  Subscriber.hh
  SubscriptionTransport.hh
  # don't include TaskGroup.hh in transport.hh
  # append it to `headers` after transport.hh is configured
  # TaskGroup.hh
  TopicManager.hh
  TransportIface.hh
  TransportTypes.hh
)

set (transport_headers "")
foreach (hdr ${headers})
  set (transport_headers "${transport_headers}#include \"gazebo/transport/${hdr}\"\n")
endforeach()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/transport.hh.in
                ${CMAKE_CURRENT_BINARY_DIR}/transport.hh )




