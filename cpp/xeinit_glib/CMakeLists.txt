set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
cmake_minimum_required(VERSION 3.0.0)
project(xeinit_glib VERSION 9.0.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
include_directories(.)
include_directories(..)

#Find PkgConfig to use glib
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
include_directories(${GLIB2_INCLUDE_DIRS})
link_directories(${GLIB2_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} main.c)
set(CMAKE_EXTAR_FLAGS ${GLIB2_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} ${GLIB2_LIBRARIES})
