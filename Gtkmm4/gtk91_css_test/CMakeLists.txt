set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0.0)
project(gtk91 VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
include_directories(..)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTKMM4 REQUIRED gtkmm-4.0)
include_directories (${GTKMM4_INCLUDE_DIRS})
link_directories (${GTKMM4_LIBRARY_DIRS})

add_executable(gtk91 src/main.cc src/resources.cpp)

IF(WIN32)
	SET(CMAKE_EXE_LINKER_FLAGS -mwindows)
ENDIF(WIN32)

add_definitions (${GTKMM4_CFLAGS_OTHER})
target_link_libraries (${PROJECT_NAME} ${GTKMM4_LIBRARIES})
