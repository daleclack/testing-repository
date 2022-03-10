# Project for gettext i18n test
project('gtk125-i18n','cpp',
        version: '1.0.0',
        license: 'GPL3+',
        default_options : ['c_std=c17', 'cpp_std=c++17'])

# Compile resources
gnome = import('gnome')

resources = gnome.compile_resources(
    'my_resources', 'res/gtk125.gresource.xml',
    source_dir: 'res',
    c_name: 'resources'
)

# Use i18n module for gettext
i18n = import('i18n')

gettext_package = 'gtk125'
add_project_arguments('-DGETTEXT_PACKAGE=' + gettext_package, language: 'cpp')

# locale directory
subdir('po')

# Add custom include directories
include_dir = include_directories('..')

# Import Gtkmm
gtk = dependency('gtkmm-3.0')

# Sources
src = ['src/main.cc','src/MyPrefs.cc','src/MyWin.cc', '../cfgfile/cfgfile.cc']

# For windows, add a icon resource
if host_machine.system() == 'windows'
    win=import('windows')
    icon_res=win.compile_resources('../icon.rc')
    executable('gtk125-i18n', src, resources, icon_res, dependencies : gtk,  
                include_directories: include_dir)
else
    executable('gtk125-i18n', src, resources, dependencies : gtk, 
                include_directories: include_dir)
endif
