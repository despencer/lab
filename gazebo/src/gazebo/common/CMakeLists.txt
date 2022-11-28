add_library(gazebo_common OBJECT 
  Base64.cc
  CommonIface.cc
  Console.cc
  Event.cc
  Events.cc
  Exception.cc
  FuelModelDatabase.cc
  Image.cc
  ModelDatabase.cc
  SemanticVersion.cc
  SphericalCoordinates.cc
  SystemPaths.cc
  Time.cc)

target_include_directories(gazebo_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR} ${SDFormat_INCLUDE_DIRS}
  ${ignition-common3_INCLUDE_DIRS} ${ignition-fuel_tools4_INCLUDE_DIRS} )

set_property(
  SOURCE SystemPaths.cc ModelDatabase.cc Console.cc
  PROPERTY COMPILE_DEFINITIONS
  GAZEBO_PLUGIN_PATH="${GAZEBO_PLUGIN_PATH}"
  GAZEBO_MODEL_PATH="${GAZEBO_MODEL_PATH}"
  GAZEBO_RESOURCE_PATH="${GAZEBO_RESOURCE_PATH}"
  GAZEBO_MODEL_DATABASE_URI="${GAZEBO_MODEL_DATABASE_URI}"
  GAZEBO_DEFAULT_MASTER_PORT=${GAZEBO_DEFAULT_MASTER_PORT}
  OGRE_RESOURCE_PATH="${OGRE_RESOURCE_PATH}"
)
