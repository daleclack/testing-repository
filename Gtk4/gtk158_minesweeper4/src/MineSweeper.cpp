#include "MineSweeper.h"
#include "MineCell.h"
#include <cstdlib>
#include <string>

// The status of the minesweeper game
typedef enum
{
    Running,
    Winned,
    Ended,
    Paused
} GameStatus;

struct _MineSweeper
{
    GtkApplicationWindow parent_instance;

    // Child widgets
    GtkWidget *main_box, *btn_box;
    GtkWidget *mine_grid;
    GtkWidget *time_label;
    MineCell *cell[49];
    GtkWidget *btn_start, *btn_show, *btn_exit;

    // Tags for game status
    int time_count;
    gboolean started;
    int mines_clear, mine_count;
    GameStatus game_status;
};

G_DEFINE_TYPE(MineSweeper, mine_sweeper, GTK_TYPE_APPLICATION_WINDOW)

static void mine_sweeper_lost(MineSweeper *self, int explode_index)
{
    for (int i = 0; i < 49; i++)
    {
    }
    gtk_widget_set_sensitive(self->mine_grid, FALSE);
}

static void find_mines(int i, int j, MineCell **cell)
{
    gboolean has_mine, cleared;
    int mines_around, x, y;
    int index1, index2;
    int mines = 0;
    // The Search cell should not over the grids
    for (index1 = MAX(0, i - 1); index1 < MIN(i + 1, 6) + 1; index1++)
    {
        for (index2 = MAX(0, j - 1); index2 < MIN(j + 1, 6) + 1; index2++)
        {
            mine_cell_get_configs(cell[index1 * 7 + index2], has_mine, cleared, mines_around, x, y);
            if (has_mine)
            {
                // cell[i * 7 + j].mines_around++;
                mines++;
            }
        }
    }

    // Update config of mine cell
    mine_cell_get_configs(cell[i * 7 + j], has_mine, cleared, mines_around, x, y);
    mine_cell_set_configs(cell[i * 7 + j], has_mine, cleared, mines, x, y);
}

static void mine_sweeper_reset(MineSweeper *self, int mines)
{
    gboolean has_mine, cleared;
    int mines_around, x, y;
    // Reset mines status
    self->mines_clear = 0;
    self->mine_count = 0;

    // Reset cell icons
    MineCell **cells = self->cell;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            gtk_button_set_icon_name(GTK_BUTTON(cells[i * 7 + j]), "");
            mine_cell_set_configs(cells[i * 7 + j], FALSE, FALSE, 0, j, i);
        }
    }

    // Add mines
    while (self->mine_count < mines)
    {
        int i = g_random_int_range(0, 49);
        mine_cell_get_configs(cells[i], has_mine, cleared, mines_around, x, y);
        if (!has_mine)
        {
            mine_cell_set_configs(cells[i], TRUE, FALSE, 0, x, y);
            self->mine_count++;
        }
    }

    // Calculate mines around a cell
    // Calculate the mines around a cell
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            find_mines(i, j, cells);
        }
    }
}

static void mine_cell_clicked(MineCell *cell, MineSweeper *self)
{
    gboolean has_mine, cleared;
    int mines_around, x, y;

    // Take all properties
    mine_cell_get_configs(cell, has_mine, cleared, mines_around, x, y);
    g_print("(%d,%d) %d %d %d\n", x, y, has_mine, cleared, mines_around);
}

static void mine_sweeper_cells_init(MineSweeper *self, int width, int height)
{
    // The mine sweeper will be 7x7
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            MineCell *cell = mine_cell_new();
            (self->cell)[i * width + j] = cell;
            g_signal_connect(cell, "clicked", G_CALLBACK(mine_cell_clicked), self);
        }
    }

    // Append mines to grid
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            GtkWidget *widget = GTK_WIDGET((self->cell)[i * width + j]);
            gtk_grid_attach(GTK_GRID(self->mine_grid), widget, j, i, 1, 1);
            mine_cell_set_configs((self->cell)[i * width + j], FALSE, FALSE, 0, j, i);
        }
    }
}

static gboolean time_func(gpointer data)
{
    MineSweeper *mine_app = MINE_SWEEPER(data);
    char tmp[50];
    (mine_app->time_count)++;
    sprintf(tmp, "Time:%d", mine_app->time_count);
    gtk_label_set_label(GTK_LABEL(mine_app->time_label), tmp);
    return mine_app->started;
}

static void btnstart_clicked(GtkButton *btn, MineSweeper *self)
{
    // Reset mine status
    mine_sweeper_reset(self, 9);

    // Start game
    gtk_widget_set_sensitive(self->mine_grid, TRUE);
    self->time_count = 0;
    self->started = TRUE;
    g_timeout_add(1000, time_func, self);
}

static void btnshow_clicked(GtkButton *btn, MineSweeper *self)
{
}

static void mine_sweeper_init(MineSweeper *self)
{
    // Initalize window
    gtk_window_set_title(GTK_WINDOW(self), "MineSweeper");

    // Create widgets
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->mine_grid = gtk_grid_new();
    self->time_label = gtk_label_new("");
    self->btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->btn_start = gtk_button_new_with_label("Start/Reset");
    self->btn_show = gtk_button_new_with_label("Show All");
    self->btn_exit = gtk_button_new_with_label("Exit");
    g_signal_connect(self->btn_start, "clicked", G_CALLBACK(btnstart_clicked), self);
    g_signal_connect(self->btn_show, "clicked", G_CALLBACK(btnshow_clicked), self);
    g_signal_connect_swapped(self->btn_exit, "clicked", G_CALLBACK(gtk_window_close), self);

    // Create mine cells
    mine_sweeper_cells_init(self, 7, 7);
    gtk_widget_set_halign(self->time_label, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(self->mine_grid, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(self->btn_box, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(self->main_box), self->time_label);
    gtk_box_append(GTK_BOX(self->main_box), self->mine_grid);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_start);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_show);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_exit);
    gtk_box_append(GTK_BOX(self->main_box), self->btn_box);
    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void mine_sweeper_class_init(MineSweeperClass *klass)
{
}

MineSweeper *mine_sweeper_new()
{
    return MINE_SWEEPER(g_object_new(mine_sweeper_get_type(), NULL));
}
