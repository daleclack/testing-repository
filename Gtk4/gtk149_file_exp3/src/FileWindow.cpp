#include "FileWindow.h"
#include "FileColumnView.h"
#include "FileGridView.h"

enum SyncMode
{
    MODEL_COLUMN_TO_GRID,
    MODEL_GRID_TO_COLUMN
};

enum ViewMode
{
    MODE_LIST,
    MODE_GRID
};

struct _FileWindow
{
    GtkApplicationWindow parent_instance;
    GListModel *model_column, *model_grid;
    GtkWidget *column_view, *grid_view;
    GtkWidget *main_box, *btn_box;
    GtkWidget *scrolled_window_column, *scrolled_window_grid;
    GtkWidget *stack;
    GtkWidget *folder_entry;
    GtkWidget *btn_up, *btn_home, *btn_new, *btn_del, *btn_view;
    GtkWidget *separator;
    ViewMode view_mode;
};

G_DEFINE_TYPE(FileWindow, file_window, GTK_TYPE_APPLICATION_WINDOW)

static GFile *file_window_get_file(FileWindow *win)
{
    GFile *file = NULL;
    if (win->view_mode == ViewMode::MODE_LIST)
    {
        // In list view mode, get current directory from the model1
        file = gtk_directory_list_get_file(GTK_DIRECTORY_LIST(win->model_column));
    }
    else
    {
        // In list view mode, get current directory from the model2
        file = gtk_directory_list_get_file(GTK_DIRECTORY_LIST(win->model_grid));
    }
    return file;
}

static void sync_models(gpointer model1, gpointer model2, SyncMode mode)
{
    if (mode == SyncMode::MODEL_COLUMN_TO_GRID)
    {
        // Set the file from model1
        GFile *file = gtk_directory_list_get_file(GTK_DIRECTORY_LIST(model1));
        if (file)
        {
            gtk_directory_list_set_file(GTK_DIRECTORY_LIST(model2), file);
        }
        // g_object_unref(file);
    }
    else
    {
        // Set the file from model2
        GFile *file = gtk_directory_list_get_file(GTK_DIRECTORY_LIST(model2));
        if (file)
        {
            gtk_directory_list_set_file(GTK_DIRECTORY_LIST(model1), file);
        }
        // g_object_unref(file);
    }
}

static void btnview_clicked(GtkButton *button, FileWindow *win)
{
    if (win->view_mode == ViewMode::MODE_LIST)
    {
        // Sync the models
        sync_models(win->model_column, win->model_grid, SyncMode::MODEL_COLUMN_TO_GRID);

        // Change view mode from list to grid
        gtk_stack_set_visible_child(GTK_STACK(win->stack), win->scrolled_window_grid);
        gtk_button_set_icon_name(button, "filewin-view-grid");
        win->view_mode = ViewMode::MODE_GRID;
    }
    else
    {
        // Sync the models
        sync_models(win->model_column, win->model_grid, SyncMode::MODEL_GRID_TO_COLUMN);

        // Change view mode from grid to list
        gtk_stack_set_visible_child(GTK_STACK(win->stack), win->scrolled_window_column);
        gtk_button_set_icon_name(button, "filewin-view-list");
        win->view_mode = ViewMode::MODE_LIST;
    }
}

static void btnup_clicked(GtkWidget *widget, FileWindow *win)
{
    // Get current directory and set to the new list
    GFile *file = file_window_get_file(win);
    char *path_str = g_file_get_path(file);
    if (!(g_str_equal(path_str, "/") || (path_str[2] = '\\' && strlen(path_str) == 3)))
    {
        GFile *file1 = g_file_get_parent(file);

        // Set the directory of models
        gtk_directory_list_set_file(GTK_DIRECTORY_LIST(win->model_column), file1);
        gtk_directory_list_set_file(GTK_DIRECTORY_LIST(win->model_grid), file1);

        // Update string in the entry for path
        char *path = g_file_get_path(file1);
        gtk_editable_set_text(GTK_EDITABLE(win->folder_entry), path);
        g_free(path);

        g_object_unref(file1);
    }
    else
    {
        GFile *file1 = g_file_new_for_path("/");

        // Set the directory of models
        gtk_directory_list_set_file(GTK_DIRECTORY_LIST(win->model_column), file1);
        gtk_directory_list_set_file(GTK_DIRECTORY_LIST(win->model_grid), file1);

        // Update string in the entry for path
        char *path = g_file_get_path(file1);
        gtk_editable_set_text(GTK_EDITABLE(win->folder_entry), path);
        g_free(path);

        g_object_unref(file1);
    }
}

static void btnok_clicked(GtkWidget *widget, GtkWidget *dialog)
{
    // Get entry widget and the content of entry
    GtkWidget *entry_new = gtk_widget_get_first_child(dialog);
    const char *file_name = gtk_editable_get_text(GTK_EDITABLE(entry_new));

    // Get the parent dir of file
    FileWindow *win = FILE_WINDOW(gtk_window_get_transient_for(GTK_WINDOW(dialog)));
    GFile *file = file_window_get_file(win);
    char *parent_dir = g_file_get_path(file);
    char *path = NULL;

    // Create a new folder
    if (parent_dir[strlen(parent_dir) - 1] != '/')
    {
        path = g_strdup_printf("%s/%s", parent_dir, file_name);
    }
    else
    {
        path = g_strdup_printf("%s%s", parent_dir, file_name);
    }
    if (g_mkdir_with_parents(path, 0755) == -1)
    {
        g_print("Error Occured!");
    }
    // g_print("%s\n", path);

    g_free(parent_dir);
    g_free(path);
    gtk_window_destroy(GTK_WINDOW(dialog));
}

static void btnnew_clicked(GtkWidget *widget, FileWindow *win)
{
    GtkWidget *dialog_new;

    // Create the window
    dialog_new = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog_new), "Create Folder");
    gtk_window_set_transient_for(GTK_WINDOW(dialog_new), GTK_WINDOW(win));

    // Add the entry and the "OK" button
    GtkWidget *header, *btn_ok, *entry_new;
    header = gtk_header_bar_new();
    btn_ok = gtk_button_new_with_label("OK");
    entry_new = gtk_entry_new();

    // Link signal for "OK" button
    g_signal_connect(entry_new, "activate", G_CALLBACK(btnok_clicked), dialog_new);
    g_signal_connect(btn_ok, "clicked", G_CALLBACK(btnok_clicked), dialog_new);

    // Add widgets to window
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), btn_ok);
    gtk_window_set_titlebar(GTK_WINDOW(dialog_new), header);
    gtk_window_set_child(GTK_WINDOW(dialog_new), entry_new);

    gtk_window_present(GTK_WINDOW(dialog_new));
}

static void btnhome_clicked(GtkWidget *widget, FileWindow *win)
{
    // Set Current dir to home dir
    GFile *file = g_file_new_for_path(g_get_home_dir());

    // Update string in the entry for path
    char *path = g_file_get_path(file);
    gtk_editable_set_text(GTK_EDITABLE(win->folder_entry), path);
    g_free(path);

    gtk_directory_list_set_file(GTK_DIRECTORY_LIST(win->model_column), file);
    gtk_directory_list_set_file(GTK_DIRECTORY_LIST(win->model_grid), file);
    g_object_unref(file);
}

static void btndel_clicked(GtkWidget *widget, FileWindow *win)
{
    GtkWidget *error_dialog;

    // Create dialog
    error_dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
    gtk_window_set_transient_for(GTK_WINDOW(error_dialog), GTK_WINDOW(win));

    // Add a header bar
    GtkWidget *header = gtk_header_bar_new();
    GtkWidget *btn_ok = gtk_button_new_with_label("OK");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), btn_ok);
    gtk_window_set_titlebar(GTK_WINDOW(error_dialog), header);
    g_signal_connect_swapped(btn_ok, "clicked", G_CALLBACK(gtk_window_destroy), error_dialog);

    // Add a label and a icon to show error
    GtkWidget *dialog_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *image = gtk_image_new_from_resource("/org/gtk/daleclack/dialog-error.png");
    GtkWidget *label = gtk_label_new("Failed to delete file");
    gtk_image_set_pixel_size(GTK_IMAGE(image), 48);

    // Add widgets to the dialog
    gtk_widget_set_margin_bottom(dialog_box, 20);
    gtk_widget_set_margin_end(dialog_box, 20);
    gtk_widget_set_margin_start(dialog_box, 20);
    gtk_widget_set_margin_top(dialog_box, 20);
    gtk_box_append(GTK_BOX(dialog_box), image);
    gtk_box_append(GTK_BOX(dialog_box), label);
    gtk_window_set_child(GTK_WINDOW(error_dialog), dialog_box);

    gtk_window_present(GTK_WINDOW(error_dialog));
}

static void folder_entry_activated(GtkWidget *widget, FileWindow *win)
{
    // Get Path and create a associated file
    const char *path = gtk_editable_get_text(GTK_EDITABLE(widget));
    GFile *file = g_file_new_for_path(path);

    // Set the directory of models
    gtk_directory_list_set_file(GTK_DIRECTORY_LIST(win->model_column), file);
    gtk_directory_list_set_file(GTK_DIRECTORY_LIST(win->model_grid), file);
}

GListModel *file_window_get_grid_model(FileWindow *self)
{
    // Get Model for grid view
    return self->model_grid;
}

GListModel *file_window_get_column_model(FileWindow *self)
{
    // Get Model for list column view
    return self->model_column;
}

GtkWidget *file_window_get_folder_entry(FileWindow *self)
{
    // Get the entry widget
    return self->folder_entry;
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
    gtk_window_set_title(GTK_WINDOW(self), "My Finder");
    gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(self), 640, 400);

    // Create list model
    GFile *file = g_file_new_for_path(g_get_home_dir());
    self->model_column = G_LIST_MODEL(gtk_directory_list_new(
        "standard::name,standard::display-name,standard::icon,standard::size,standard::content-type", file));

    self->model_grid = G_LIST_MODEL(gtk_directory_list_new(
        "standard::name,standard::display-name,standard::icon,standard::size,standard::content-type", file));

    // Create column view widget
    self->column_view = create_column_view(self);

    // Create grid view widget
    self->grid_view = create_grid_view(self);

    // Create buttons
    self->btn_up = gtk_button_new_from_icon_name("filewin-go-up");
    self->btn_home = gtk_button_new_from_icon_name("filewin-go-home");
    self->btn_new = gtk_button_new_from_icon_name("filewin-new");
    self->btn_del = gtk_button_new_from_icon_name("filewin-delete");
    self->btn_view = gtk_button_new_from_icon_name("filewin-view-list");

    // Create entry for show and change the current folder
    self->folder_entry = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(self->folder_entry), g_get_home_dir());

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
    g_signal_connect(self->btn_up, "clicked", G_CALLBACK(btnup_clicked), self);
    g_signal_connect(self->btn_home, "clicked", G_CALLBACK(btnhome_clicked), self);
    g_signal_connect(self->btn_del, "clicked", G_CALLBACK(btndel_clicked), self);
    g_signal_connect(self->btn_new, "clicked", G_CALLBACK(btnnew_clicked), self);
    g_signal_connect(self->folder_entry, "activate", G_CALLBACK(folder_entry_activated), self);

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

    gtk_box_append(GTK_BOX(self->main_box), self->btn_box);      // Box for control buttons
    gtk_box_append(GTK_BOX(self->main_box), self->folder_entry); // Box for folder switcher
    gtk_box_append(GTK_BOX(self->main_box), self->stack);        // Box for main area
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
