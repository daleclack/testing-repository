#A Simple Project Test
project('gtk108', 'cpp',
        default_options : ['c_std=c17', 'cpp_std=c++17'])

#Initalize variants
gnome=import('gnome')

#Compile Resource 
gresources = gnome.compile_resources(
    'resources', 'res/gtk108.resource.xml',
    source_dir: 'res',
    c_name: 'resources'
)

#compile schemas
app_schemas = gnome.compile_schemas(depend_files: 'org.gtk.daleclack.gschema.xml')

#The Gtkmm Library as a dependency
gtkdep = dependency('gtkmm-3.0')

#Additional include dirs
dir_include = include_directories('..')

#source files
src=['src/main.cc', 'src/MyWin.cc']

#Use Different Build Opinions in windows and Linux
if host_machine.system() == 'windows'
    win=import('windows')
    icon_res=win.compile_resources('../icon.rc')
    executable('gtk108', icon_res, src, gresources, dependencies : gtkdep, app_schemas, 
                win_subsystem : 'windows', include_directories : dir_include)
else
    executable('gtk108', src, gresources, app_schemas, dependencies : gtkdep, include_directories : dir_include)
endif
