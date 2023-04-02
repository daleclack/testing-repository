#include "MainWin.h"

struct _MainWin
{
    GtkApplicationWindow parent_instance;
    GListModel *model;
    GtkWidget *view;
    GtkListItemFactory *factory;
    GtkSingleSelection *selection;
    GtkWidget *main_box;
    GtkWidget *scrolled_window;
    GtkWidget *btn_add, *btn_remove, *btn_remove_all;
    GtkWidget *entry_add;
};

G_DEFINE_TYPE(MainWin, main_win, GTK_TYPE_APPLICATION_WINDOW)

static void setup_filename_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Create label to show list item
    GtkWidget *label;
    label = gtk_label_new(" ");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_list_item_set_child(item, label);
}

static void bind_filename_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Get child for list item
    GtkWidget *label;
    label = gtk_list_item_get_child(item);

    // Get string and add the string to the label
    GFileInfo *info = G_FILE_INFO(gtk_list_item_get_item(item));
    const char *display_name = g_file_info_get_display_name(info);
    gtk_label_set_label(GTK_LABEL(label), display_name);
}

static void setup_filetype_item(GtkListItemFactory *factory, GtkListItem *item){
    // Create label to show list item
    GtkWidget *label;
    label = gtk_label_new(" ");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_list_item_set_child(item, label);
}

static void bind_filetype_item(GtkListItemFactory *factory, GtkListItem *item){
    // Get child for list item
    GtkWidget *label;
    label = gtk_list_item_get_child(item);

    // Get string and set it to the label
    GFileInfo *info = G_FILE_INFO(gtk_list_item_get_item(item));
    const char *type_str = g_file_info_get_content_type(info);
    gtk_label_set_label(GTK_LABEL(label), type_str);
}

static void setup_filesize_item(GtkListItemFactory *factory, GtkListItem *item){
    // Create label to show list item
    GtkWidget *label;
    label = gtk_label_new(" ");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_list_item_set_child(item, label);
}

static void bind_filesize_item(GtkListItemFactory *factory, GtkListItem *item){
    // Get child for list item
    GtkWidget *label;
    label = gtk_list_item_get_child(item);

    // Get string and set it to the label
    GFileInfo *info = G_FILE_INFO(gtk_list_item_get_item(item));
    const char *size_str = g_format_size(g_file_info_get_size(info));
    gtk_label_set_label(GTK_LABEL(label), size_str);
}

static void main_win_dispose(GObject *object)
{
    // Clear List Model
    // g_list_store_remove_all(G_LIST_STORE(MAIN_WIN(object)->model));
    G_OBJECT_CLASS(main_win_parent_class)->dispose(object);
}

static void main_win_init(MainWin *self)
{
    GtkColumnViewColumn *column;
    // Initalize window
    gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(self), 640, 360);

    // Create list model
    GFile *file = g_file_new_for_path(g_get_home_dir());
    self->model = G_LIST_MODEL(gtk_directory_list_new(
        "standard::name,standard::display-name,standard::icon,standard::size,standard::content-type", file));

    // Create view
    self->selection = gtk_single_selection_new(self->model);
    self->view = gtk_column_view_new(GTK_SELECTION_MODEL(self->selection));

    // Create Factory for file name
    self->factory = gtk_signal_list_item_factory_new();
    g_signal_connect(self->factory, "setup", G_CALLBACK(setup_filename_item), NULL);
    g_signal_connect(self->factory, "bind", G_CALLBACK(bind_filename_item), NULL);
    column = gtk_column_view_column_new("Name", self->factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(self->view), column);
    g_object_unref(column);

    // Create Factory for file type
    self->factory = gtk_signal_list_item_factory_new();
    g_signal_connect(self->factory, "setup", G_CALLBACK(setup_filetype_item), NULL);
    g_signal_connect(self->factory, "bind", G_CALLBACK(bind_filetype_item), NULL);
    column = gtk_column_view_column_new("Type", self->factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(self->view), column);
    g_object_unref(column);

    // Create Factory for file size
    self->factory = gtk_signal_list_item_factory_new();
    g_signal_connect(self->factory, "setup", G_CALLBACK(setup_filesize_item), NULL);
    g_signal_connect(self->factory, "bind", G_CALLBACK(bind_filesize_item), NULL);
    column = gtk_column_view_column_new("Size", self->factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(self->view), column);
    g_object_unref(column);

    // Create widgets for layout
    self->scrolled_window = gtk_scrolled_window_new();
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Link signals

    // Add widgets to the layout
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand(self->scrolled_window, TRUE);
    gtk_widget_set_vexpand(self->scrolled_window, TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->scrolled_window), self->view);
    gtk_box_append(GTK_BOX(self->main_box), self->scrolled_window);
    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void main_win_class_init(MainWinClass *klass)
{
    G_OBJECT_CLASS(klass)->dispose = main_win_dispose;
}

MainWin *main_win_new(GtkApplication *app)
{
    return MAIN_WIN(g_object_new(main_win_get_type(), "application", app, NULL));
}
