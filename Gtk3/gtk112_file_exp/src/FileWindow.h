#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(FileWindow,file_window,FILE,WINDOW,GtkApplicationWindow)

FileWindow * file_window_new(GtkApplication *app);
