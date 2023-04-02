#include "FileWindow.h"
#include "FileColumnView.h"
#include "FileGridView.h"

enum SyncMode{
    MODEL1_TO_2,
    MODEL2_TO_1
};

enum ViewMode{
    MODE_LIST,
    MODE_GRID
};

struct _FileWindow
{
    GtkApplicationWindow parent_instance;
    GListModel *model1, *model2;
    GtkWidget *column_view, *grid_view;
    GtkWidget *main_box, *btn_box;
    GtkWidget *scrolled_window_column, *scrolled_window_grid;
    GtkWidget *stack;
    GtkWidget *btn_up, *btn_home, *btn_new, *btn_del, *btn_view;
    GtkWidget *separator;
    ViewMode view_mode;
};

G_DEFINE_TYPE(FileWindow, file_window, GTK_TYPE_APPLICATION_WINDOW)

static void sync_models(gpointer model1, gpointer model2, SyncMode mode){
    if(mode == SyncMode::MODEL1_TO_2){
        // Set the file from model1
        GFile *file = gtk_directory_list_get_file(GTK_DIRECTORY_LIST(model1));
        gtk_directory_list_set_file(GTK_DIRECTORY_LIST(model2), file);
        // g_object_unref(file);
    }else{
        // Set the file from model2
        GFile *file = gtk_directory_list_get_file(GTK_DIRECTORY_LIST(model2));
        gtk_directory_list_set_file(GTK_DIRECTORY_LIST(model1), file);
        // g_object_unref(file);
    }
}

static void btnview_clicked(GtkButton *button, FileWindow *win){
    if(win->view_mode == ViewMode::MODE_LIST){
        // Sync the models
        sync_models(win->model1, win->model2, SyncMode::MODEL1_TO_2);

        // Change view mode from list to grid
        gtk_stack_set_visible_child(GTK_STACK(win->stack), win->scrolled_window_grid);
        gtk_button_set_icon_name(button, "view-grid");
        win->view_mode = ViewMode::MODE_GRID;
    }else{
        // Sync the models
        sync_models(win->model1, win->model2, SyncMode::MODEL2_TO_1);

        // Change view mode from grid to list
        gtk_stack_set_visible_child(GTK_STACK(win->stack), win->scrolled_window_column);
        gtk_button_set_icon_name(button, "view-list");
        win->view_mode = ViewMode::MODE_LIST;
    }
}

static void btnup_clicked(GtkWidget *widget, FileWindow *win){

}

static void btnnew_clicked(GtkWidget *widget, FileWindow *win){

}

static void btndel_clicked(GtkWidget *widget, FileWindow *win){
    
}

static void file_window_dispose(GObject *object)
{
    // Clear List Model
    G_OBJECT_CLASS(file_window_parent_class)->dispose(object);
}

static void file_window_init(FileWindow *self)
{
    GtkColumnViewColumn *column;
    // Initalize window
    gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(self), 640, 400);

    // Create list model
    GFile *file = g_file_new_for_path(g_get_home_dir());
    self->model1 = G_LIST_MODEL(gtk_directory_list_new(
        "standard::name,standard::display-name,standard::icon,standard::size,standard::content-type", file));

    self->model2 = G_LIST_MODEL(gtk_directory_list_new(
        "standard::name,standard::display-name,standard::icon,standard::size,standard::content-type", file));

    // Create column view widget
    self->column_view = create_column_view(self->model1);

    // Create grid view widget
    self->grid_view = create_grid_view(self->model2);

    // Create buttons
    self->btn_up = gtk_button_new_from_icon_name("go-up");
    self->btn_home = gtk_button_new_from_icon_name("go-home");
    self->btn_new = gtk_button_new_from_icon_name("folder-new");
    self->btn_del = gtk_button_new_from_icon_name("edit-delete");
    self->btn_view = gtk_button_new_from_icon_name("view-list");

    // Create widgets for layout
    self->scrolled_window_column = gtk_scrolled_window_new();
    self->scrolled_window_grid = gtk_scrolled_window_new();
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->stack = gtk_stack_new();
    self->separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    // Add buttons to the btn_box
    gtk_widget_set_hexpand(self->btn_box, TRUE);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_up);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_home);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_new);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_del);
    gtk_widget_set_hexpand(self->separator, TRUE);
    // gtk_widget_set_halign(self->btn_view, GTK_ALIGN_END);
    gtk_box_append(GTK_BOX(self->btn_box), self->separator);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_view);

    // Link signals
    g_signal_connect(self->btn_view, "clicked", G_CALLBACK(btnview_clicked), self);

    // Add scrolled window for columns view
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->scrolled_window_column),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand(self->scrolled_window_column, TRUE);
    gtk_widget_set_vexpand(self->scrolled_window_column, TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->scrolled_window_column), self->column_view);
    gtk_stack_add_named(GTK_STACK(self->stack), self->scrolled_window_column, "Column View");
    
    // Add scrolled window for grid view
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->scrolled_window_grid),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand(self->scrolled_window_grid, TRUE);
    gtk_widget_set_vexpand(self->scrolled_window_grid, TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->scrolled_window_grid), self->grid_view);
    gtk_stack_add_named(GTK_STACK(self->stack), self->scrolled_window_grid, "Grid View");
    gtk_box_append(GTK_BOX(self->main_box), self->btn_box);
    gtk_box_append(GTK_BOX(self->main_box), self->stack);
    // gtk_stack_set_visible_child(GTK_STACK(self->stack), self->scrolled_window_grid);
    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void file_window_class_init(FileWindowClass *klass)
{
    G_OBJECT_CLASS(klass)->dispose = file_window_dispose;
}

FileWindow *file_window_new(GtkApplication *app)
{
    return FILE_WINDOW(g_object_new(file_window_get_type(), "application", app, NULL));
}
