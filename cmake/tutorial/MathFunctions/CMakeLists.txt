# TODO 1: Add a library called MathFunctions
# Hint: You will need the add_library command

add_library(MathFunctions OBJECT mysqrt.cc)

target_include_directories(MathFunctions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(MathFunctions tut_compiler_flags)

set(inst_libs MathFunctions tut_compiler_flags)
install(TARGETS ${inst_libs} DESTINATION lib)
install (FILES MathFunctions.h DESTINATION include)