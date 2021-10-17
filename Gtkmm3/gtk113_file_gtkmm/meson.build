#A Simple Project Test
project('gtk113', 'cpp',
        default_options : ['c_std=c17', 'cpp_std=c++17'])

#Initalize variants
gnome=import('gnome')

#Compile Resource 
gresources = gnome.compile_resources(
    'resources', '../default_res/default.gresource.xml',
    source_dir: '../default_res',
    c_name: 'resources'
)

#compile schemas
# app_schemas = gnome.compile_schemas(depend_files: 'org.gtk.daleclack.gschema.xml')

#The Gtkmm Library as a dependency
gtkdep = dependency('gtkmm-3.0')

#Additional include dirs
dir_include = include_directories('..')

#source files
src = ['src/main.cc', 'src/FileWindow.cc']

#Use Different Build Opinions in windows and Linux
if host_machine.system() == 'windows'
    win=import('windows')
    icon_res=win.compile_resources('../icon.rc')
    executable('gtk113', icon_res, src, dependencies : gtkdep, gresources, 
                win_subsystem : 'windows', include_directories : dir_include)
else
    executable('gtk113', src, gresources, dependencies : gtkdep, include_directories : dir_include)
endif
