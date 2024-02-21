#include "MineSweeper.h"
#include "MineCell.h"

struct _MineSweeper
{
    GtkApplicationWindow parent_instance;
    GtkWidget *main_box, *btn_box;
    GtkWidget *mine_grid;
    GtkWidget *time_label;
    MineCell *cell[49];
    GtkWidget *btn_start, *btn_show, *btn_exit;
    int time_count;
    gboolean started;
};

G_DEFINE_TYPE(MineSweeper, mine_sweeper, GTK_TYPE_APPLICATION_WINDOW)

static void mine_sweeper_cells_init(MineSweeper *self, int width, int height)
{
    // The mine sweeper will be 7x7
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            (self->cell)[i * width + j] = mine_cell_new();
        }
    }

    // Append mines to grid
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            GtkWidget *widget = GTK_WIDGET((self->cell)[i * width + j]);
            gtk_grid_attach(GTK_GRID(self->mine_grid), widget, j, i, 1, 1);
        }
    }
}

static void mine_sweeper_reset(MineSweeper *self)
{
    // Reset mines status

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
    // Start game
    self->time_count = 0;
    self->started = TRUE;
    g_timeout_add(1000, time_func, self);
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
