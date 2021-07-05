#A Simple Project Test
project('gtk93', 'cpp',
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
gtkdep = dependency('gtkmm-4.0')

#Use Different Build Opinions in windows and Linux
if host_machine.system() == 'windows'
    win=import('windows')
    icon_res=win.compile_resources('icon.rc')
    executable('gtk93', icon_res, 'src/main.cc', 'src/MyWin.cc', dependencies : gtkdep,
				win_subsystem : 'windows')
else
    executable('gtk93', 'src/main.cc', 'src/MyWin.cc', dependencies : gtkdep)
endif
