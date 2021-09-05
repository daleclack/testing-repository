#A Simple Project Test
project('gtk107', 'cpp',
        default_options : ['c_std=c17', 'cpp_std=c++17'])

#Initalize variants
gnome=import('gnome')

#Compile Resource 
gresources = gnome.compile_resources(
    'resources', 'res/gtk107.gresource.xml',
    source_dir: 'res',
    c_name: 'resources'
)

#compile schemas
app_schemas = gnome.compile_schemas(depend_files: 'org.gtk.daleclack.gschema.xml')

#The Gtkmm Library as a dependency
gtkdep = dependency('gtk4')

#Additional include dirs
dir_include = include_directories('..')

#source files
src = ['src/main.cpp', 'src/myapplication.cpp', 'src/mywindow.cpp', 'src/MyDialog.cpp', 'src/myprefs.cpp']

#Use Different Build Opinions in windows and Linux
if host_machine.system() == 'windows'
    win=import('windows')
    icon_res=win.compile_resources('../icon.rc')
    executable('gtk107', icon_res, src, gresources, app_schemas, dependencies : gtkdep, 
                win_subsystem : 'windows', include_directories : dir_include)
else
    executable('gtk107', src, gresources, app_schemas, dependencies : gtkdep, include_directories : dir_include)
endif
