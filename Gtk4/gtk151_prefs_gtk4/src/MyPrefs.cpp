#include "MyPrefs.h"
#include "MyItem.h"
#include "winpe.xpm"
#include "img7.xpm"
#include "image_types.h"
#include <string>

// File name and path limits
static const int name_max_length = 256;
static const int path_max_length = 4096;

struct _MyPrefs
{
    GtkWindow parent_instance;
    GtkBuilder *prefs_builder;
    GtkWidget *background, *back_page;
    GtkWidget *stack_box, *combo_box;

    // Widget for window size config
    GtkWidget *label_size;
    GtkWidget *sizes_drop;

    // Widget for dock position and mode
    GtkWidget *mode_check;

    // Widget for background selection
    GtkWidget *folders_view, *images_view;
    GtkWidget *btns_box, *views_box;
    GtkWidget *folders_sw, *images_sw;
    GtkWidget *btn_add, *btn_remove;

    // List stores
    GListStore *folders_list, *images_list;
    GFile *file;
    GtkDirectoryList *file_list;
    GtkSingleSelection *folders_select, *image_select;

    // Folders view
    GtkColumnViewColumn *folder_image_column;
    GtkColumnViewColumn *folder_string_column;
    GtkListItemFactory *factory_folder_image;
    GtkListItemFactory *factory_folder_string;

    // Images view
    GtkColumnViewColumn *pics_image_column;
    GtkColumnViewColumn *pics_string_column;
    GtkListItemFactory *factory_pics_image;
    GtkListItemFactory *factory_pics_string;

    // Pixbufs
    GdkPixbuf *pixbuf, *sized;
    int width, height;
    char current_folder[path_max_length], current_image[name_max_length];
};

G_DEFINE_TYPE(MyPrefs, my_prefs, GTK_TYPE_WINDOW)

static void factory_folder_image_setup(GtkListItemFactory *factory, GtkListItem *item)
{
    // Create image
    GtkWidget *image = gtk_image_new();
    gtk_image_set_pixel_size(GTK_IMAGE(image), 16);
    gtk_list_item_set_child(item, image);
}

static void factory_folder_image_bind(GtkListItemFactory *factory, GtkListItem *item)
{
    // Get Image Widget
    GtkWidget *image = gtk_list_item_get_child(item);

    // Get icon_name
    MyItem *item1 = MY_ITEM(gtk_list_item_get_item(item));
    gtk_image_set_from_icon_name(GTK_IMAGE(image), "prefs_folder");
}

static void factory_folder_string_setup(GtkListItemFactory *factory, GtkListItem *item)
{
    // Add a label
    GtkWidget *label = gtk_label_new("");
    gtk_list_item_set_child(item, label);
}

static void factory_folder_string_bind(GtkListItemFactory *factory, GtkListItem *item)
{
    // Set names from label
    GtkWidget *label = gtk_list_item_get_child(item);

    // Get display name
    MyItem *item1 = MY_ITEM(gtk_list_item_get_item(item));
    gtk_label_set_label(GTK_LABEL(label),
                        my_item_get_display_name(item1));
}

static void folder_view_init(MyPrefs *self)
{
    // Create store for folders column view
    self->folders_list = g_list_store_new(my_item_get_type());
    g_list_store_append(self->folders_list,
                        my_item_new("Default Backgrounds", ":0", TRUE));
    g_list_store_append(self->folders_list,
                        my_item_new("User's Home directory", g_get_home_dir(), FALSE));
    g_list_store_append(self->folders_list,
                        my_item_new("User's Picture directory",
                                    g_get_user_special_dir(G_USER_DIRECTORY_PICTURES),
                                    FALSE));
    self->folders_select = gtk_single_selection_new(G_LIST_MODEL(self->folders_list));
    gtk_single_selection_set_selected(self->folders_select, 0);

    // Create factories to renderer the list
    self->folders_view = gtk_column_view_new(GTK_SELECTION_MODEL(self->folders_select));

    // Image column
    self->factory_folder_image = gtk_signal_list_item_factory_new();
    g_signal_connect(self->factory_folder_image, "setup",
                     G_CALLBACK(factory_folder_image_setup), NULL);
    g_signal_connect(self->factory_folder_image, "bind",
                     G_CALLBACK(factory_folder_image_bind), NULL);
    self->folder_image_column = gtk_column_view_column_new(" ",
                                                           self->factory_folder_image);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(self->folders_view),
                                  self->folder_image_column);

    // Folder names column
    self->factory_folder_string = gtk_signal_list_item_factory_new();
    g_signal_connect(self->factory_folder_string, "setup",
                     G_CALLBACK(factory_folder_string_setup), NULL);
    g_signal_connect(self->factory_folder_string, "bind",
                     G_CALLBACK(factory_folder_string_bind), NULL);
    self->folder_string_column = gtk_column_view_column_new("Name",
                                                            self->factory_folder_string);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(self->folders_view),
                                  self->folder_string_column);
}

static void factory_pics_image_setup(GtkListItemFactory *factory, GtkListItem *item)
{
    // Create image
    GtkWidget *image = gtk_image_new();
    gtk_image_set_pixel_size(GTK_IMAGE(image), 16);
    gtk_list_item_set_child(item, image);
}

static void factory_pics_image_bind(GtkListItemFactory *factory, GtkListItem *item)
{
    // Get Image Widget
    GtkWidget *image = gtk_list_item_get_child(item);

    // Get icon_name
    MyItem *item1 = MY_ITEM(gtk_list_item_get_item(item));
    gtk_image_set_from_icon_name(GTK_IMAGE(image), "folder-images");
}

static void factory_pics_string_setup(GtkListItemFactory *factory, GtkListItem *item)
{
    // Add a label
    GtkWidget *label = gtk_label_new("");
    gtk_list_item_set_child(item, label);
}

static void factory_pics_string_bind(GtkListItemFactory *factory, GtkListItem *item)
{
    // Set names from label
    GtkWidget *label = gtk_list_item_get_child(item);

    // Get display name
    MyItem *item1 = MY_ITEM(gtk_list_item_get_item(item));
    gtk_label_set_label(GTK_LABEL(label),
                        my_item_get_display_name(item1));
}

static void images_list_default(GListStore *store1)
{
    // if the store is not empty, clear it
    if (g_list_model_get_n_items(G_LIST_MODEL(store1)))
    {
        g_list_store_remove_all(store1);
    }

    // Append default items
    g_list_store_append(store1,
                        my_item_new("img7.xpm", ":1", TRUE));
    g_list_store_append(store1,
                        my_item_new("winpe.xpm", ":2", TRUE));
}

static void update_images_list(GListStore *image_store, GListModel *dir_list, GFile *file1)
{
    // if the store is not empty, clear it
    if (g_list_model_get_n_items(G_LIST_MODEL(image_store)))
    {
        g_list_store_remove_all(image_store);
    }

    // Iterate the objects and add to the list
    for (int i = 0; i < g_list_model_get_n_items(dir_list); i++)
    {
        if (mime_type_supported())
        {
            // Get file info
            GFileInfo *info = G_FILE_INFO(g_list_model_get_item(dir_list, i));
            const char *content_type = g_file_info_get_content_type(info);
            // g_print("%s\n", content_type);
            if (strncmp(content_type, "image/", 6) == 0)
            {
                g_print("%s\n", content_type);
                const char *name = g_file_info_get_display_name(info);
                char *path = g_file_get_path(file1);
                char *image_path = g_strdup_printf("%s/%s", path, name);
                g_list_store_append(image_store,
                                    my_item_new(name, image_path, FALSE));
                g_free(path);
            }
        }
        else
        {
        }
    }
}

static void pics_view_init(MyPrefs *self)
{
    // Create store for pictures view
    self->images_list = g_list_store_new(my_item_get_type());
    images_list_default(self->images_list);

    // Create selection model for view
    self->image_select = gtk_single_selection_new(G_LIST_MODEL(self->images_list));
    gtk_single_selection_set_selected(self->image_select, 0);

    // Create column view
    self->images_view = gtk_column_view_new(GTK_SELECTION_MODEL(self->image_select));

    // Image column
    self->factory_pics_image = gtk_signal_list_item_factory_new();
    g_signal_connect(self->factory_pics_image, "setup",
                     G_CALLBACK(factory_pics_image_setup), NULL);
    g_signal_connect(self->factory_pics_image, "bind",
                     G_CALLBACK(factory_pics_image_bind), NULL);
    self->pics_image_column = gtk_column_view_column_new(" ",
                                                         self->factory_pics_image);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(self->images_view),
                                  self->pics_image_column);

    // Folder names column
    self->factory_pics_string = gtk_signal_list_item_factory_new();
    g_signal_connect(self->factory_pics_string, "setup",
                     G_CALLBACK(factory_pics_string_setup), NULL);
    g_signal_connect(self->factory_pics_string, "bind",
                     G_CALLBACK(factory_pics_string_bind), NULL);
    self->pics_string_column = gtk_column_view_column_new("Name",
                                                          self->factory_pics_string);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(self->images_view),
                                  self->pics_string_column);
}

static void update_internal_image(GtkWidget *background1, const char **id)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_xpm_data(id);
    GdkPixbuf *sized = gdk_pixbuf_scale_simple(pixbuf, 1024, 576, GDK_INTERP_BILINEAR);
    gtk_picture_set_pixbuf(GTK_PICTURE(background1), pixbuf);
    g_object_unref(pixbuf);
    g_object_unref(sized);
}

// Scan the selection of two column views
static gboolean scan_func(gpointer data)
{
    MyPrefs *prefs = MY_PREFS(data);
    // Get the selection of folders view
    // The model and item of folders view
    auto folder_model = gtk_column_view_get_model(GTK_COLUMN_VIEW(prefs->folders_view));
    auto folder_item = gtk_single_selection_get_selected_item(GTK_SINGLE_SELECTION(folder_model));

    // File name and properties
    const char *folder_name = my_item_get_path(MY_ITEM(folder_item));
    gboolean is_internal = my_item_get_internal(MY_ITEM(folder_item));

    // Check weather the selection changed
    if (strncmp(prefs->current_folder, folder_name, strlen(folder_name)) != 0)
    {
        if (is_internal)
        {
            // Update image list to default
            images_list_default(prefs->images_list);
        }
        else
        {
            // Update image list by the folder selection
            prefs->file = g_file_new_for_path(folder_name);
            gtk_directory_list_set_file(prefs->file_list, prefs->file);
            update_images_list(prefs->images_list, G_LIST_MODEL(prefs->file_list), prefs->file);
            g_object_unref(prefs->file);
        }
        strncpy(prefs->current_folder, folder_name, path_max_length);
    }

    // Get the selection of images view
    // The model and item of images view
    auto model = gtk_column_view_get_model(GTK_COLUMN_VIEW(prefs->images_view));
    auto item = gtk_single_selection_get_selected_item(GTK_SINGLE_SELECTION(model));

    // Check weather the list of images is empty
    if (g_list_model_get_n_items(G_LIST_MODEL(prefs->images_list)) == 0)
    {
        return TRUE;
    }

    // File name and properties
    const char *file_name = my_item_get_path(MY_ITEM(item));
    is_internal = my_item_get_internal(MY_ITEM(item));

    // Check weather the selection changed
    if (strncmp(prefs->current_image, file_name, strlen(file_name)) != 0)
    {
        // Update image
        if (is_internal)
        {
            // For image which is internal
            switch (file_name[1])
            {
            case '1':
                update_internal_image(prefs->background, img7);
                break;
            case '2':
                update_internal_image(prefs->background, winpe);
                break;
            }
            strncpy(prefs->current_image, file_name, name_max_length);
        }
        else
        {
            // For image which is outside
        }
    }
    return TRUE;
}

static void my_prefs_close_request(GtkWindow *self, gpointer user_data)
{
    gtk_widget_set_visible(GTK_WIDGET(self), FALSE);
}

static void my_prefs_init(MyPrefs *self)
{
    // Options strings for dropdown
    const char *strings[] = {
        "640x480",
        "800x450",
        "1024x576",
        "1280x720",
        "1366x768",
        NULL};
    self->width = 1024;
    self->height = 576;
    strncpy(self->current_image, ":0", name_max_length);
    strncpy(self->current_folder, ":0", path_max_length);

    // Initalize window
    gtk_window_set_default_size(GTK_WINDOW(self), 800, 450);
    gtk_window_set_icon_name(GTK_WINDOW(self), "My_GtkUI");

    // Create builder
    self->prefs_builder = gtk_builder_new_from_resource("/org/gtk/daleclack/prefs_stack.ui");

    // Get Objects
    self->stack_box = GTK_WIDGET(gtk_builder_get_object(self->prefs_builder, "stack_box"));
    self->back_page = GTK_WIDGET(gtk_builder_get_object(self->prefs_builder, "back_page"));
    self->combo_box = GTK_WIDGET(gtk_builder_get_object(self->prefs_builder, "combo_box"));
    self->mode_check = GTK_WIDGET(gtk_builder_get_object(self->prefs_builder, "mode_check"));
    self->label_size = GTK_WIDGET(gtk_builder_get_object(self->prefs_builder, "label_size"));

    // Initalize folder and image views and append to the box
    gtk_widget_set_margin_bottom(self->back_page, 20);
    gtk_widget_set_margin_end(self->back_page, 20);
    gtk_widget_set_margin_start(self->back_page, 20);
    gtk_widget_set_margin_top(self->back_page, 20);
    folder_view_init(self);
    pics_view_init(self);
    self->views_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->btns_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->btn_add = gtk_button_new_from_icon_name("list-add");
    self->btn_remove = gtk_button_new_from_icon_name("list-remove");

    // Pack views
    self->folders_sw = gtk_scrolled_window_new();
    gtk_widget_set_hexpand(self->folders_view, TRUE);
    gtk_widget_set_vexpand(self->folders_view, TRUE);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->folders_sw),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->folders_sw), self->folders_view);
    self->images_sw = gtk_scrolled_window_new();
    gtk_widget_set_hexpand(self->images_view, TRUE);
    gtk_widget_set_vexpand(self->images_view, TRUE);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->images_sw),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->images_sw), self->images_view);
    gtk_box_append(GTK_BOX(self->views_box), self->folders_sw);
    gtk_box_append(GTK_BOX(self->views_box), self->images_sw);
    gtk_box_append(GTK_BOX(self->back_page), self->views_box);
    gtk_box_append(GTK_BOX(self->btns_box), self->btn_add);
    gtk_box_append(GTK_BOX(self->btns_box), self->btn_remove);
    gtk_box_append(GTK_BOX(self->back_page), self->btns_box);

    // Create file list
    self->file = g_file_new_for_path(g_get_home_dir());
    self->file_list = gtk_directory_list_new(
        "standard::name,standard::display-name,standard::icon,standard::size,standard::content-type", self->file);
    g_object_unref(self->file);

    // Add a dropdown for default sizes config
    self->sizes_drop = gtk_drop_down_new_from_strings(strings);
    gtk_drop_down_set_selected(GTK_DROP_DOWN(self->sizes_drop), 2);
    gtk_box_append(GTK_BOX(self->combo_box), self->sizes_drop);

    char *size = g_strdup_printf("Current Config: %d x %d", self->width, self->height);
    gtk_label_set_label(GTK_LABEL(self->label_size), size);
    g_free(size);

    // Set default mode for check button
    gtk_check_button_set_active(GTK_CHECK_BUTTON(self->mode_check), TRUE);

    // Set Child
    gtk_window_set_child(GTK_WINDOW(self), self->stack_box);

    // Add timer to scan the list
    g_timeout_add(10, scan_func, self);

    // Close request for this window
    g_signal_connect(self, "close-request", G_CALLBACK(my_prefs_close_request), NULL);
}

static void my_prefs_class_init(MyPrefsClass *klass)
{
}

GtkWidget *my_prefs_new(GtkWidget *back, GtkWindow *parent)
{
    GtkWidget *prefs_win = GTK_WIDGET(g_object_new(my_prefs_get_type(),
                                                   "transient-for", parent, NULL));
    MY_PREFS(prefs_win)->background = back;
    return prefs_win;
}
