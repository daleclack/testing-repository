#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MineCell, mine_cell, Mine, Cell, GtkButton)

MineCell *mine_cell_new();

void mine_cell_get_configs(MineCell *cell, gboolean &cell_has_mine, gboolean &cell_cleared,
                           int &cell_mines_around, int &cell_x, int &cell_y);

void mine_cell_set_configs(MineCell *cell, gboolean cell_has_mine, gboolean cell_cleared,
                           int cell_mines_around, int cell_x, int cell_y);
