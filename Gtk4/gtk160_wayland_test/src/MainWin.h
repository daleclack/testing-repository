#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MainWin, main_win, Main, Win, GtkApplicationWindow)

MainWin *main_win_new(GtkApplication *app);