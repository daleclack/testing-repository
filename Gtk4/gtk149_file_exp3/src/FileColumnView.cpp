#include "FileColumnView.h"

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

static void listview_activated(GtkColumnView *view, guint position, GtkDirectoryList *list)
{
    // Get the model
    GtkSelectionModel *model = gtk_column_view_get_model(view);
    GFileInfo *info = G_FILE_INFO(g_list_model_get_item(G_LIST_MODEL(model), position));

    // if the file type is directory, open the directory
    if (g_file_info_get_file_type(info) == G_FILE_TYPE_DIRECTORY)
    {
        gtk_directory_list_set_file(list,
                                    G_FILE(g_file_info_get_attribute_object(info, "standard::file")));
    }
    g_object_unref(info);
}

GtkWidget *create_column_view(GListModel *model)
{
    // Create view
    GtkSingleSelection *selection = gtk_single_selection_new(model);
    GtkWidget *view = gtk_column_view_new(GTK_SELECTION_MODEL(selection));

    // Create Factory for file icon
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_fileicon_item), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_fileicon_item), NULL);
    GtkColumnViewColumn *column = gtk_column_view_column_new("Name", factory);
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
    g_signal_connect(view, "activate", G_CALLBACK(listview_activated), model);

    return view;
}