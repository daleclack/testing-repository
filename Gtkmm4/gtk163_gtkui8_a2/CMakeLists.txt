set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.10.0)
project(gtk163_gtkui8 VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../../GCR_CMake/macros)
include(GlibCompileResourcesSupport)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
include_directories(.)
include_directories(..)

#Find PkgConfig to use gtkmm
find_package (PkgConfig REQUIRED)
pkg_check_modules (GTKMM4 REQUIRED gtkmm-4.0)
include_directories (${GTKMM4_INCLUDE_DIRS})
link_directories (${GTKMM4_LIBRARY_DIRS})

#Find Gettext
# find_package (Gettext REQUIRED)
# set(PO_DIR ${CMAKE_BINARY_DIR}/po/zh_CN/LC_MESSAGES)

#Source files
set(SOURCE_FILE src/main.cc src/MainWin.cc src/MyStack.cc src/MyPanel.cc src/MyFinder.cc)

#Compile Resource

set(RESOURCE_LIST
    STRIPBLANKS cambalache/findermenu.ui
    STRIPBLANKS cambalache/mainwin.ui
    STRIPBLANKS cambalache/mypanel.ui
    STRIPBLANKS cambalache/overlaywin.ui
    winpe.png
    icons/16x16/actions/finder_audio.svg
    icons/16x16/actions/finder-battery.svg
    icons/16x16/actions/finder-computer.svg
    icons/16x16/actions/finder-wifi.svg
    icons/16x16/actions/finder_audio-dark.svg
    icons/16x16/actions/finder-battery-dark.svg
    icons/16x16/actions/finder-computer-dark.svg
    icons/16x16/actions/finder-wifi-dark.svg
    icons/16x16/actions/folder-images.svg
    icons/16x16/actions/My_GtkUI.png
    icons/16x16/actions/open-menu.svg
    icons/16x16/actions/list-add.svg
    icons/16x16/actions/list-remove.svg
    icons/16x16/actions/prefs_folder.svg
    icons/48x48/actions/dialog-error.png
    icons/48x48/actions/game.png
    icons/48x48/actions/game_bottom.png
    icons/48x48/actions/game_right.png
    icons/48x48/actions/game_running.png
    icons/48x48/actions/btnabout.png
    icons/48x48/actions/My_GtkUI.png
    icons/scalable/status/1mines.svg
    icons/scalable/status/2mines.svg
    icons/scalable/status/3mines.svg
    icons/scalable/status/4mines.svg
    icons/scalable/status/5mines.svg
    icons/scalable/status/6mines.svg
    icons/scalable/status/7mines.svg
    icons/scalable/status/8mines.svg
    icons/scalable/status/exploded.svg
    icons/scalable/status/flag.svg
    icons/scalable/status/incorrect.svg
    icons/scalable/status/maybe.svg
    icons/scalable/status/mine.svg
    icons/scalable/status/24game.svg
    icons/scalable/status/24game_bottom.svg
    icons/scalable/status/24game_right.svg
    icons/scalable/status/24game_running.svg
    icons/scalable/status/audacious_whitesur.svg
    icons/scalable/status/my_prefs.svg
    icons/scalable/status/my_prefs_bottom.svg
    icons/scalable/status/my_prefs_right.svg
    icons/scalable/status/my_prefs_running.svg
    icons/scalable/status/drawing_app.svg
    icons/scalable/status/drawing_app_bottom.svg
    icons/scalable/status/drawing_app_right.svg
    icons/scalable/status/drawing_app_running.svg
    icons/scalable/status/finder-find.svg
    icons/scalable/status/finder-find-dark.svg
    icons/scalable/status/file-app.svg
    icons/scalable/status/file-app_bottom.svg
    icons/scalable/status/file-app_right.svg
    icons/scalable/status/file-app_running.svg
    icons/scalable/status/filewin-delete.svg
    icons/scalable/status/filewin-go-home.svg
    icons/scalable/status/filewin-go-up.svg
    icons/scalable/status/filewin-new.svg
    icons/scalable/status/filewin-view-grid.svg
    icons/scalable/status/filewin-view-list.svg
    icons/scalable/status/display_prefs.svg
    icons/scalable/status/myrunner.svg
    icons/scalable/status/image_app.svg
    icons/scalable/status/image_app_bottom.svg
    icons/scalable/status/image_app_right.svg
    icons/scalable/status/image_app_running.svg
    icons/scalable/status/my_textedit.svg
    icons/scalable/status/my_textedit_bottom.svg
    icons/scalable/status/my_textedit_right.svg
    icons/scalable/status/my_textedit_running.svg
    icons/scalable/status/vlc_whitesur.svg
    icons/scalable/status/my_trash.svg
    icons/scalable/status/circle.svg
    icons/scalable/status/circle-dark.svg
    icons/scalable/status/freehand.svg
    icons/scalable/status/freehand-dark.svg
    icons/scalable/status/line.svg
    icons/scalable/status/line-dark.svg
    icons/scalable/status/rectangle.svg
    icons/scalable/status/rectangle-dark.svg
    icons/scalable/status/calcapp.svg
    icons/scalable/status/calcapp_bottom.svg
    icons/scalable/status/calcapp_right.svg
    icons/scalable/status/calcapp_running.svg
    icons/scalable/status/header_close.svg
    icons/scalable/status/header_minimize.svg
    icons/scalable/status/mines_app.svg
    icons/scalable/status/mines_app_bottom.svg
    icons/scalable/status/mines_app_right.svg
    icons/scalable/status/mines_app_running.svg
    icons/scalable/status/media-app.svg
    icons/scalable/status/media-app_bottom.svg
    icons/scalable/status/media-app_right.svg
    icons/scalable/status/media-app_running.svg
    icons/scalable/status/media-eject-dark.svg
    icons/scalable/status/media-eject.svg
    icons/scalable/status/media-mount-dark.svg
    icons/scalable/status/media-mount.svg
    icons/scalable/status/media-playback-pause-dark.svg
    icons/scalable/status/media-playback-pause.svg
    icons/scalable/status/media-playback-start-dark.svg
    icons/scalable/status/media-playback-start.svg
    icons/scalable/status/media-playback-stop-dark.svg
    icons/scalable/status/media-playback-stop.svg
    icons/scalable/status/media-playlist-append-dark.svg
    icons/scalable/status/media-playlist-append.svg
    icons/scalable/status/media-playlist-normal-dark.svg
    icons/scalable/status/media-playlist-normal.svg
    icons/scalable/status/media-playlist-play-dark.svg
    icons/scalable/status/media-playlist-play.svg
    icons/scalable/status/media-playlist-repeat-dark.svg
    icons/scalable/status/media-playlist-repeat-one-dark.svg
    icons/scalable/status/media-playlist-repeat.svg
    icons/scalable/status/media-playlist-repeat-one.svg
    icons/scalable/status/media-playlist-shuffle-dark.svg
    icons/scalable/status/media-playlist-shuffle.svg
    icons/scalable/status/media-seek-backward-dark.svg
    icons/scalable/status/media-seek-backward.svg
    icons/scalable/status/media-seek-forward-dark.svg
    icons/scalable/status/media-seek-forward.svg
    icons/scalable/status/media-skip-backward-dark.svg
    icons/scalable/status/media-skip-backward.svg
    icons/scalable/status/media-skip-forward-dark.svg
    icons/scalable/status/media-skip-forward.svg
    )

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
	SET(CMAKE_RC_COMPILER windres)
	set(app_WINRC ../icon.rc)
	set_property(SOURCE ../icon.rc APPEND PROPERTY
        OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/../icon.ico
        )
	add_executable(${PROJECT_NAME} ${app_WINRC} ${SOURCE_FILE} ${RESOURCE_FILE})
    add_custom_command(PRE_BUILD TARGET ${PROJECT_NAME} 
                        COMMAND echo * > ${CMAKE_BINARY_DIR}/.gitignore
                        COMMAND echo **/* > ${CMAKE_BINARY_DIR}/.hgignore)
else()
	add_executable(${PROJECT_NAME} ${SOURCE_FILE} ${RESOURCE_FILE})
    add_custom_command(PRE_BUILD TARGET ${PROJECT_NAME}
                        COMMAND echo \"*\" > ${CMAKE_BINARY_DIR}/.gitignore
                        COMMAND echo \"**/*\" > ${CMAKE_BINARY_DIR}/.hgignore)   
endif(WIN32)

#Add command to generate .gitignore and .mo files
# add_custom_command( TARGET ${PROJECT_NAME} 
#                     COMMAND mkdir -p ${PO_DIR}
#                     COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} ${CMAKE_SOURCE_DIR}/po/zh_CN.po -o ${PO_DIR}/${PROJECT_NAME}.mo)

SET (CMAKE_EXTRA_CXX_FLAGS ${GTKMM4_CFLAGS_OTHER})
target_link_libraries (${PROJECT_NAME} ${GTKMM4_LIBRARIES} -lpthread)
