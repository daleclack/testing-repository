#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MyPrefs, my_prefs, MY, PREFS, GtkWindow)

GtkWidget *my_prefs_new(GtkWidget *back, GtkWindow *parent);
