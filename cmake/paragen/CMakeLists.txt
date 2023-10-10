cmake_minimum_required(VERSION 3.15)

project(paragen VERSION 1.0)

find_package(Python REQUIRED)
execute_process(COMMAND ${Python_EXECUTABLE} -c "import jinja2" RESULT_VARIABLE RET)
if(NOT RET EQUAL 0)
    message(FATAL_ERROR "Missing jinja2")
endif()