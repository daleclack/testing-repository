#include "FileWindow.h"
#include "FileColumnView.h"
#include "FileGridView.h"

struct _FileWindow
{
    GtkApplicationWindow parent_instance;
    GListModel *model;
    GtkWidget *column_view;
    GtkWidget *main_box;
    GtkWidget *scrolled_window;
};

G_DEFINE_TYPE(FileWindow, file_window, GTK_TYPE_APPLICATION_WINDOW)




static void file_window_dispose(GObject *object)
{
    // Clear List Model
    // g_list_store_remove_all(G_LIST_STORE(file_window(object)->model));
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
    self->model = G_LIST_MODEL(gtk_directory_list_new(
        "standard::name,standard::display-name,standard::icon,standard::size,standard::content-type", file));

    // Create column view widget
    self->column_view = create_column_view(self->model);

    // Create widgets for layout
    self->scrolled_window = gtk_scrolled_window_new();
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Add widgets to the layout
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand(self->scrolled_window, TRUE);
    gtk_widget_set_vexpand(self->scrolled_window, TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->scrolled_window), self->column_view);
    gtk_box_append(GTK_BOX(self->main_box), self->scrolled_window);
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
