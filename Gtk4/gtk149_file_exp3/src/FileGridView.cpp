#include "FileGridView.h"

static void setup_grid_item(GtkListItemFactory *factory, GtkListItem *item)
{
    GtkWidget *under_box, *info_box;
    GtkWidget *image;
    GtkWidget *label_filename, *label_filetype, *label_filesize;
    // Create box for file icon and file info
    under_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    image = gtk_image_new();
    label_filename = gtk_label_new(" ");
    label_filetype = gtk_label_new(" ");
    label_filesize = gtk_label_new(" ");

    // Pack widgets
    gtk_image_set_pixel_size(GTK_IMAGE(image), 48);
    gtk_box_append(GTK_BOX(under_box), image);
    gtk_box_append(GTK_BOX(info_box), label_filename);
    gtk_box_append(GTK_BOX(info_box), label_filetype);
    gtk_box_append(GTK_BOX(info_box), label_filesize);
    gtk_box_append(GTK_BOX(under_box), info_box);

    gtk_list_item_set_child(item, under_box);
}

static void bind_grid_item(GtkListItemFactory *factory, GtkListItem *item)
{
    GtkWidget *under_box, *info_box;
    GtkWidget *image;
    GtkWidget *label_filename, *label_filetype, *label_filesize;
    // Get Widgets
    under_box = gtk_list_item_get_child(item);
    image = gtk_widget_get_first_child(under_box);
    info_box = gtk_widget_get_next_sibling(image);
    label_filename = gtk_widget_get_first_child(info_box);
    label_filetype = gtk_widget_get_next_sibling(label_filename);
    label_filesize = gtk_widget_get_next_sibling(label_filetype);

    // Get GFileInfo
    GFileInfo *info = G_FILE_INFO(gtk_list_item_get_item(item));

    // The icon for file or folders
    gtk_image_set_from_gicon(GTK_IMAGE(image), g_file_info_get_icon(info));

    // File name, content type and size
    gtk_label_set_label(GTK_LABEL(label_filename), g_file_info_get_display_name(info));
    gtk_label_set_label(GTK_LABEL(label_filetype), g_file_info_get_content_type(info));
    gtk_label_set_label(GTK_LABEL(label_filesize), g_format_size(g_file_info_get_size(info)));
}

GtkWidget *create_grid_view(GListModel *model)
{
    // Create factory
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_grid_item), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_grid_item), NULL);

    // Create view
    GtkSingleSelection *selection = gtk_single_selection_new(model);
    GtkWidget *grid_view = gtk_grid_view_new(GTK_SELECTION_MODEL(selection), factory);

    return grid_view;
}
