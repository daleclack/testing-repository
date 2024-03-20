#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(TestWin, test_win, Test, Win, GtkWindow)

TestWin *test_win_new(GtkWindow *parent);