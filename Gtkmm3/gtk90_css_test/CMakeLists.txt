set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0.0)
project(gtk90 VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
include_directories(..)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTKMM3 REQUIRED gtkmm-3.0)
include_directories (${GTKMM3_INCLUDE_DIRS})
link_directories (${GTKMM3_LIBRARY_DIRS})

#Compile a resource.cpp file

# Step 1:
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

set(GRESOURCE_C   resource.c)
set(GRESOURCE_XML gtk89.resource.xml)

# Step 2:
add_custom_command(
    OUTPUT ${GRESOURCE_C}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/res
    COMMAND ${GLIB_COMPILE_RESOURCES}
    ARGS
		${GRESOURCE_XML}
        --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C} 
		--generate-source
)

# Step 3:
add_custom_target(
    my-gresource
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
)

# Step 4:Add the resource to compile list and compile
#For win32 platform,use rc resource and .ico icon
if(WIN32)
SET(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
	set(app_WINRC icon.rc)
	set_property(SOURCE icon.rc APPEND PROPERTY
        OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/icon.ico
        )
	add_executable(gtk90 WIN32 ${app_WINRC} src/main.cc ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})
else()
	add_executable(gtk90 src/main.cc ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})
endif(WIN32)

set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
    PROPERTIES GENERATED TRUE
)

# Step 5:Add Dependencies and link
add_dependencies(${PROJECT_NAME} my-gresource)

SET (CMAKE_EXTRA_CXX_FLAGS ${GTKMM3_CFLAGS_OTHER})
target_link_libraries (${PROJECT_NAME} ${GTKMM3_LIBRARIES})
