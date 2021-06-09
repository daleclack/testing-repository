set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0.0)
project(gtk69 VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)
include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})
add_executable(gtk69 src/main.cpp src/winconf.cpp src/resources.cpp)
add_definitions (${GTK3_CFLAGS_OTHER})
target_link_libraries (${PROJECT_NAME} ${GTK3_LIBRARIES})
