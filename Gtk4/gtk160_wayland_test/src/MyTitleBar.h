#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MyTitleBar, my_titlebar, My, TitleBar, GObject)

void my_titlebar_set_window(MyTitleBar *title_bar, GtkWidget *window);

MyTitleBar *my_titlebar_new();