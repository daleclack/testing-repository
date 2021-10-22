set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0.0)
project(gtk112 VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../../GCR_CMake/macros)
include(GlibCompileResourcesSupport)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
include_directories(.)
include_directories(..)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)
include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})

#Compile Resource
set(RESOURCE_LIST
    gnome-fs-directory.png
    gnome-fs-regular.png
    view-grid-symbolic.png
    view-list-symbolic.png
    dialog-error.png)

compile_gresources(RESOURCE_FILE
                   XML_OUT
                   TYPE EMBED_C
                   RESOURCES ${RESOURCE_LIST}
                   PREFIX "gtk112"
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
	add_executable(gtk112 WIN32 ${app_WINRC} src/main.cpp src/FileWindow.cpp ${RESOURCE_FILE})
else()
	add_executable(gtk112 src/main.cpp src/FileWindow.cpp ${RESOURCE_FILE})

endif(WIN32)

SET (CMAKE_EXTRA_CXX_FLAGS ${GTK3_CFLAGS_OTHER})
target_link_libraries (${PROJECT_NAME} ${GTK3_LIBRARIES} -lpthread)
