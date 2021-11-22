#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MyWindow,my_window,MY,WINDOW,GtkApplicationWindow)

MyWindow * my_window_new(GtkApplication * application);
