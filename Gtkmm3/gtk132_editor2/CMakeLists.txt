set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0.0)
project(gtk131_calc2 VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../../GCR_CMake/macros)
include(GlibCompileResourcesSupport)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
include_directories(.)
include_directories(..)

#Find PkgConfig to use gtkmm3
find_package (PkgConfig REQUIRED)
pkg_check_modules (GTKMM3 REQUIRED gtkmm-3.0)
include_directories (${GTKMM3_INCLUDE_DIRS})
link_directories (${GTKMM3_LIBRARY_DIRS})

#Find Gettext
find_package (Gettext REQUIRED)
set(PO_DIR ${CMAKE_BINARY_DIR}/po/zh_CN/LC_MESSAGES)

#Source files
set(SOURCE_FILE src/main.cc src/TextEditor.cc)

#Compile Resource

set(RESOURCE_LIST
    text_menu.xml)

compile_gresources(RESOURCE_FILE
                   XML_OUT
                   TYPE EMBED_C
                   RESOURCES ${RESOURCE_LIST}
                   PREFIX "/org/gtk/daleclack"
                   SOURCE_DIR ${PROJECT_SOURCE_DIR}/res)
                   
# Add a custom target to the makefile. Now make builds our resource file.
# It depends on the output RESOURCE_FILE.

add_custom_target(resource ALL DEPENDS ${RESOURCE_FILE})

#For win32 platform,use rc resource and .ico icon
if(WIN32)
	SET(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
	set(app_WINRC ../icon.rc)
	set_property(SOURCE ../icon.rc APPEND PROPERTY
        OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/../icon.ico
        )
	add_executable(${PROJECT_NAME} WIN32 ${app_WINRC} ${SOURCE_FILE} ${RESOURCE_FILE})
    add_custom_command( TARGET ${PROJECT_NAME} 
                        COMMAND echo * > ${CMAKE_BINARY_DIR}/.gitignore
                        COMMAND echo **/* > ${CMAKE_BINARY_DIR}/.hgignore)
else()
	add_executable(${PROJECT_NAME} ${SOURCE_FILE} ${RESOURCE_FILE})
    add_custom_command( TARGET ${PROJECT_NAME}
                        COMMAND echo \"*\" > ${CMAKE_BINARY_DIR}/.gitignore
                        COMMAND echo \"**/*\" > ${CMAKE_BINARY_DIR}/.hgignore)   
endif(WIN32)

#Add command to generate .gitignore and .mo files
# add_custom_command( TARGET ${PROJECT_NAME} 
#                     COMMAND mkdir -p ${PO_DIR}
#                     COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} ${CMAKE_SOURCE_DIR}/po/zh_CN.po -o ${PO_DIR}/${PROJECT_NAME}.mo)

SET (CMAKE_EXTRA_CXX_FLAGS ${GTKMM3_CFLAGS_OTHER})
target_link_libraries (${PROJECT_NAME} ${GTKMM3_LIBRARIES} -lpthread)
