#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MainWin, main_win, Main, Win, GtkApplicationWindow)

// Returns the MainWin Type
#define MAIN_WIN_TYPE (main_win_get_type())

// Creates a new MainWin Object
MainWin *main_win_new(GtkApplication *app);
