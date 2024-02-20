#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MineSweeper, mine_sweeper, MINE, SWEEPER, GtkApplicationWindow)

MineSweeper *mine_sweeper_new();
