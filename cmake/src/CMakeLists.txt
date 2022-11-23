# TODO 1: Set the minimum required version of CMake to be 3.10
cmake_minimum_required(VERSION 3.15)

# TODO 2: Create a project named Tutorial
project(Tutorial VERSION 1.0)

add_library(tut_compiler_flags INTERFACE)
target_compile_features(tut_compiler_flags INTERFACE cxx_std_11)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(tut_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)


option(USE_MYMATH "Use self-implemented math" ON)

configure_file(TutorialConfig.h.in TutorialConfig.h)

if(USE_MYMATH)
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
endif()

# TODO 3: Add an executable called Tutorial to the project
# Hint: Be sure to specify the source file as tutorial.cxx
add_executable(tut tutorial.cc)

target_link_libraries(tut PUBLIC ${EXTRA_LIBS} tut_compiler_flags)
target_include_directories(tut PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS tut DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

enable_testing()
add_test(NAME Runs COMMAND tut 25)
add_test(NAME Usage COMMAND tut)
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number*")
add_test(NAME StandardUse COMMAND tut 4)
set_tests_properties(StandardUse PROPERTIES PASS_REGULAR_EXPRESSION "4 is 2")

function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

do_test(tut 4 "4 is 2")
do_test(tut 9 "9 is 3")
do_test(tut 5 "5 is 2.236")
do_test(tut 7 "7 is 2.645")
do_test(tut 25 "25 is 5")
do_test(tut -25 "-25 is (-nan|nan|0)")
do_test(tut 0.0001 "0.0001 is 0.01")
