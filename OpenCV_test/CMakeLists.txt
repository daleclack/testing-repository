cmake_minimum_required(VERSION 3.0.0)
project(OpenCV_test VERSION 1.0.0)

#Find the opencv package
find_package(OpenCV REQUIRED)

#include directories for opencv
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(OpenCV_test main.cpp)

#Add command to generate .gitignore
add_custom_command(TARGET ${PROJECT_NAME} 
                   COMMAND echo \"*\" > ${CMAKE_BINARY_DIR}/.gitignore
                   COMMAND echo \"**/*\" > ${CMAKE_BINARY_DIR}/.hgignore)

#Add OpenCV Libraries
target_link_libraries(OpenCV_test ${OpenCV_LIBS})
