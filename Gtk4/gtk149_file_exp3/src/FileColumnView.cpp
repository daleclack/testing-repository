#include "FileColumnView.h"
#include "GetFileType.h"

static void setup_fileicon_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Create Image for icon
    GtkWidget *image;
    image = gtk_image_new();
    gtk_image_set_pixel_size(GTK_IMAGE(image), 24);
    gtk_list_item_set_child(item, image);
}

static void bind_fileicon_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Get the image widget
    GtkWidget *image;
    image = gtk_list_item_get_child(item);

    // Set image for column
    GFileInfo *info = G_FILE_INFO(gtk_list_item_get_item(item));
    gtk_image_set_from_gicon(GTK_IMAGE(image), g_file_info_get_icon(info));
}

static void setup_filename_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Create label to show list item
    GtkWidget *label;
    label = gtk_label_new(" ");

    // Set the mode for ellipsize
    gtk_label_set_ellipsize(GTK_LABEL(label), PANGO_ELLIPSIZE_END);
    gtk_label_set_width_chars(GTK_LABEL(label), 20);

    // Add the label to the item
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

static void setup_filetype_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Create label to show list item
    GtkWidget *label;
    label = gtk_label_new(" ");

    // Set the mode for ellipsize
    gtk_label_set_ellipsize(GTK_LABEL(label), PANGO_ELLIPSIZE_END);
    gtk_label_set_width_chars(GTK_LABEL(label), 10);

    // Add the label to the item
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_list_item_set_child(item, label);
}

static void bind_filetype_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Get child for list item
    GtkWidget *label;
    label = gtk_list_item_get_child(item);

    // Get string and set it to the label
    GFileInfo *info = G_FILE_INFO(gtk_list_item_get_item(item));
    const char *type_str = g_file_info_get_content_type(info);
    gtk_label_set_label(GTK_LABEL(label), type_str);
}

static void setup_filesize_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Create label to show list item
    GtkWidget *label;
    label = gtk_label_new(" ");
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_list_item_set_child(item, label);
}

static void bind_filesize_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Get child for list item
    GtkWidget *label;
    label = gtk_list_item_get_child(item);

    // Get string and set it to the label
    GFileInfo *info = G_FILE_INFO(gtk_list_item_get_item(item));
    const char *size_str = g_format_size(g_file_info_get_size(info));
    gtk_label_set_label(GTK_LABEL(label), size_str);
}

static void listview_activated(GtkColumnView *view, guint position, FileWindow *win)
{
    // Get the model
    GtkSelectionModel *model = gtk_column_view_get_model(view);
    GFileInfo *info = G_FILE_INFO(g_list_model_get_item(G_LIST_MODEL(model), position));
    GtkDirectoryList *list = GTK_DIRECTORY_LIST(file_window_get_column_model(win));

    // if the file type is directory, open the directory
    if (check_directory(info))
    {
        // Get the file and set it to the GtkDirectoryList
        GFile *file = G_FILE(g_file_info_get_attribute_object(info, "standard::file"));
        gtk_directory_list_set_file(list, file);

        // Update string in the entry for path
        char *path = g_file_get_path(file);
        gtk_editable_set_text(GTK_EDITABLE(file_window_get_folder_entry(win)), path);
        // g_print("%s\n", path);
        g_free(path);
    }
    g_object_unref(info);
}

GtkWidget *create_column_view(FileWindow *win)
{
    // Create view
    GListModel *model = file_window_get_column_model(win);
    GtkSingleSelection *selection = gtk_single_selection_new(model);
    GtkWidget *view = gtk_column_view_new(GTK_SELECTION_MODEL(selection));

    // Create Factory for file icon
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_fileicon_item), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_fileicon_item), NULL);
    GtkColumnViewColumn *column = gtk_column_view_column_new(" ", factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), column);
    g_object_unref(column);

    // Create Factory for file name
    factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_filename_item), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_filename_item), NULL);
    column = gtk_column_view_column_new("Name", factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), column);
    g_object_unref(column);

    // Create Factory for file type
    factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_filetype_item), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_filetype_item), NULL);
    column = gtk_column_view_column_new("Type", factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), column);
    g_object_unref(column);

    // Create Factory for file size
    factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_filesize_item), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_filesize_item), NULL);
    column = gtk_column_view_column_new("Size", factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), column);
    g_object_unref(column);

    // Link signals
    g_signal_connect(view, "activate", G_CALLBACK(listview_activated), win);

    return view;
}
