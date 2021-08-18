#A Simple Project Test
project('gtk103', 'cpp',
        default_options : ['c_std=c17', 'cpp_std=c++17'])

#Initalize variants
# gnome=import('gnome')

#Compile Resource 
# gresources = gnome.compile_resources(
#     'resources', 'res/gtk91.resource.xml',
#     source_dir: 'res',
#     c_name: 'resources'
# )

#The Gtkmm Library as a dependency
gtkdep = dependency('gtkmm-3.0')

#Additional include dirs
dir_include = include_directories('..')

#source files
src=['src/main.cc', 'src/MyWin.cc', 'src/SetDialog.cc', '../cfgfile2/cfgfile.cc']

#Use Different Build Opinions in windows and Linux
if host_machine.system() == 'windows'
    win=import('windows')
    icon_res=win.compile_resources('../icon.rc')
    executable('gtk103', icon_res, src, dependencies : gtkdep, 
                win_subsystem : 'windows', include_directories : dir_include)
else
    executable('gtk103', src, dependencies : gtkdep, include_directories : dir_include)
endif
