#include "MyPrefs.h"
#include "MyItem.h"
#include "winpe.xpm"
#include "img7.xpm"
#include <string>

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
    char current_image[256];
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
                        my_item_new("Default Backgrounds", "", TRUE));
    g_list_store_append(self->folders_list,
                        my_item_new("User's Home directory", g_get_home_dir(), FALSE));
    g_list_store_append(self->folders_list,
                        my_item_new("User's Picture directory",
                                    g_get_user_special_dir(G_USER_DIRECTORY_PICTURES),
                                    FALSE));
    self->folders_select = gtk_single_selection_new(G_LIST_MODEL(self->folders_list));

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

static void pics_view_init(MyPrefs *self)
{
    // Create store for pictures view
    self->images_list = g_list_store_new(my_item_get_type());
    g_list_store_append(self->images_list,
                        my_item_new("img7.xpm", ":1", TRUE));
    g_list_store_append(self->images_list,
                        my_item_new("winpe.xpm", ":2", TRUE));

    // Create selection model for view
    self->image_select = gtk_single_selection_new(G_LIST_MODEL(self->images_list));

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
    // Get the seletion of images view
    auto model = gtk_column_view_get_model(GTK_COLUMN_VIEW(prefs->images_view));
    auto item = gtk_single_selection_get_selected_item(GTK_SINGLE_SELECTION(model));
    const char *file_name = my_item_get_path(MY_ITEM(item));
    gboolean is_internal = my_item_get_internal(MY_ITEM(item));
    if (strncmp(prefs->current_image, file_name, strlen(file_name)) != 0)
    {
        // Update image
        if (is_internal)
        {
            switch (file_name[1])
            {
            case '1':
                update_internal_image(prefs->background, img7);
                break;
            case '2':
                update_internal_image(prefs->background, winpe);
                break;
            }
            strncpy(prefs->current_image, file_name, 256);
        }
        else
        {
        }
    }
    return TRUE;
}

static void my_prefs_close_request(GtkWindow *self, gpointer user_data){
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
    strncpy(self->current_image, ":1", 256);

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
    g_timeout_add(16, scan_func, self);

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
