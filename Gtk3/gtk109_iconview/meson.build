#A Simple Project Test
project('gtk109', 'cpp',
        default_options : ['c_std=c17', 'cpp_std=c++17'])

#Initalize variants
gnome=import('gnome')

#Compile Resource 
gresources = gnome.compile_resources(
    'resources', 'res/gtk109.gresource.xml',
    source_dir: 'res',
    c_name: 'resources'
)

#compile schemas
# app_schemas = gnome.compile_schemas(depend_files: 'org.gtk.daleclack.gschema.xml')

#The Gtkmm Library as a dependency
gtkdep = dependency('gtk+-3.0')

#Additional include dirs
dir_include = include_directories('..')

#source files
src = ['src/main.cpp']

#Use Different Build Opinions in windows and Linux
if host_machine.system() == 'windows'
    win=import('windows')
    icon_res=win.compile_resources('../icon.rc')
    executable('gtk109', icon_res, src, gresources, dependencies : gtkdep, 
                win_subsystem : 'windows', include_directories : dir_include)
else
    executable('gtk109', src, gresources, dependencies : gtkdep, include_directories : dir_include)
endif
