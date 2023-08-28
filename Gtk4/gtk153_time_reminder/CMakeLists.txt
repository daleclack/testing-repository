set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.5.0)
project(gtk153_time_reminder VERSION 1.0.0)

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
pkg_check_modules (GTK4 REQUIRED gtk4)
include_directories (${GTK4_INCLUDE_DIRS})
link_directories (${GTK4_LIBRARY_DIRS})

#Find Gettext
# find_package (Gettext REQUIRED)
# set(PO_DIR ${CMAKE_BINARY_DIR}/po/zh_CN/LC_MESSAGES)

#Source files
set(SOURCE_FILE src/main.cpp src/MyReminder.cpp)

#Compile Resource

# set(RESOURCE_LIST
#     icons/16x16/actions/folder-images.svg
#     icons/16x16/actions/list-add.svg
#     icons/16x16/actions/list-remove.svg
#     icons/16x16/actions/My_GtkUI.png
#     icons/16x16/actions/prefs_folder.svg
#     icons/48x48/actions/dialog-error.png
#     icons/48x48/actions/My_GtkUI.png
#     icons/scalable/status/display_prefs.svg
#     prefs_stack.ui
#     )

# compile_gresources(RESOURCE_FILE
#                    XML_OUT
#                    TYPE EMBED_C
#                    RESOURCES ${RESOURCE_LIST}
#                    PREFIX "/org/gtk/daleclack"
#                    SOURCE_DIR ${PROJECT_SOURCE_DIR}/res)
               
# Add a custom target to the makefile. Now make builds our resource file.
# It depends on the output RESOURCE_FILE.

# add_custom_target(resource ALL DEPENDS ${RESOURCE_FILE})

#For win32 platform,use rc resource and .ico icon
if(WIN32)
	SET(CMAKE_RC_COMPILER windres)
	set(app_WINRC ../icon.rc)
	set_property(SOURCE ../icon.rc APPEND PROPERTY
        OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/../icon.ico
        )
	add_executable(${PROJECT_NAME} WIN32 ${app_WINRC} ${SOURCE_FILE})
    add_custom_command( TARGET ${PROJECT_NAME} 
                        COMMAND echo * > ${CMAKE_BINARY_DIR}/.gitignore
                        COMMAND echo **/* > ${CMAKE_BINARY_DIR}/.hgignore)
else()
	add_executable(${PROJECT_NAME} ${SOURCE_FILE})
    add_custom_command( TARGET ${PROJECT_NAME}
                        COMMAND echo \"*\" > ${CMAKE_BINARY_DIR}/.gitignore
                        COMMAND echo \"**/*\" > ${CMAKE_BINARY_DIR}/.hgignore)   
endif(WIN32)

#Add command to generate .gitignore and .mo files
# add_custom_command( TARGET ${PROJECT_NAME} 
#                     COMMAND mkdir -p ${PO_DIR}
#                     COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} ${CMAKE_SOURCE_DIR}/po/zh_CN.po -o ${PO_DIR}/${PROJECT_NAME}.mo)

SET (CMAKE_EXTRA_CXX_FLAGS ${GTK4_CFLAGS_OTHER})
target_link_libraries (${PROJECT_NAME} ${GTK4_LIBRARIES} -lpthread)
