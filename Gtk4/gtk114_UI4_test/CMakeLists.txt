set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0.0)
project(gtk114 VERSION 1.0.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
include_directories(.)
include_directories(..)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK4 REQUIRED gtk4)
include_directories (${GTK4_INCLUDE_DIRS})
link_directories (${GTK4_LIBRARY_DIRS})

set(SOURCES src/main.cpp)

# Step 4:Add the resource to compile list and compile
if(WIN32)
    set(app_WINRC icon.rc)
	set_property(SOURCE icon.rc APPEND PROPERTY
        OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/icon.ico
        )
    add_executable(${PROJECT_NAME} WIN32 ${app_WINRC} ${SOURCES} ${RESOURCE_FILE})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCE_FILE})
endif(WIN32)

#Add command to generate .gitignore
add_custom_command(TARGET ${PROJECT_NAME} 
                   COMMAND echo \"*\" > ${CMAKE_BINARY_DIR}/.gitignore
                   COMMAND echo \"**/*\" > ${CMAKE_BINARY_DIR}/.hgignore)

SET (CMAKE_EXTRA_CXX_FLAGS ${GTK4_CFLAGS_OTHER})
target_link_libraries (${PROJECT_NAME} ${GTK4_LIBRARIES} -lpthread -lm)
