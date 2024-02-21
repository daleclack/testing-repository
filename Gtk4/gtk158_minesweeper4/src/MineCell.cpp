#include "MineCell.h"

struct _MineCell
{
    GtkButton parent_instance;
    gboolean has_mine = FALSE;
    gboolean cleared = FALSE;
    int mines_around;
    int x, y;
};

G_DEFINE_TYPE(MineCell, mine_cell, GTK_TYPE_BUTTON)

static void mine_cell_init(MineCell *self)
{
    gtk_button_set_icon_name(GTK_BUTTON(self), "");
    // gtk_button_set_has_frame(GTK_BUTTON(self), FALSE);
    gtk_widget_set_size_request(GTK_WIDGET(self), 40, 40);
    self->mines_around = 0;
    self->has_mine = FALSE;
}

static void mine_cell_class_init(MineCellClass *klass)
{
}

void mine_cell_get_configs(MineCell *cell, gboolean &cell_has_mine, gboolean &cell_cleared,
                           int &cell_mines_around, int &cell_x, int &cell_y)
{
    cell_has_mine = cell->has_mine;
    cell_cleared = cell->cleared;
    cell_mines_around = cell->mines_around;
    cell_x = cell->x;
    cell_y = cell->y;
}

void mine_cell_set_configs(MineCell *cell, gboolean cell_has_mine, gboolean cell_cleared,
                           int cell_mines_around, int cell_x, int cell_y)
{
    cell->has_mine = cell_has_mine;
    cell->cleared = cell_cleared;
    cell->mines_around = cell_mines_around;
    cell->x = cell_x;
    cell->y = cell_y;
}

MineCell *mine_cell_new()
{
    return Mine_Cell(g_object_new(mine_cell_get_type(), NULL));
}
