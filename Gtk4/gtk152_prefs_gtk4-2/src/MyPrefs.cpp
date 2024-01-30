#include "MyPrefs.h"
#include "MyItem.h"
#include "winpe.xpm"
#include "img7.xpm"
#include "image_types.h"
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
    int current_folder_index, current_image_index;
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
    gtk_widget_set_halign(label, GTK_ALIGN_START);
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
    gtk_widget_set_halign(label, GTK_ALIGN_START);
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

static void update_images_list(MyPrefs *prefs1)
{
    // if the store is not empty, clear it
    if (g_list_model_get_n_items(G_LIST_MODEL(prefs1->images_list)))
    {
        g_list_store_remove_all(prefs1->images_list);
    }

    // Iterate the objects and add to the list
    for (int i = 0; i < g_list_model_get_n_items(G_LIST_MODEL(prefs1->file_list)); i++)
    {
        if (mime_type_supported())
        {
            // Get file info
            GFileInfo *info = G_FILE_INFO(g_list_model_get_item(
                G_LIST_MODEL(prefs1->file_list), i));
            const char *content_type = g_file_info_get_content_type(info);

            // Append image file info to the list
            // Check content type
            if (strncmp(content_type, "image/", 6) == 0)
            {
                // Add properties to the list
                const char *name = g_file_info_get_display_name(info);
                char *path = g_file_get_path(prefs1->file);
                char *image_path = g_strdup_printf("%s/%s", path, name);
                g_list_store_append(prefs1->images_list,
                                    my_item_new(name, image_path, FALSE));
                g_free(path);
            }
        }
        else
        {
            // Get file info
            GFileInfo *info = G_FILE_INFO(g_list_model_get_item(
                G_LIST_MODEL(prefs1->file_list), i));
            const char *content_type = g_file_info_get_content_type(info);
            char *pattern = g_strdup_printf("*%s", content_type);

            // Append image file info to the list
            for (int i = 0; supported_globs[i] != NULL; i++)
            {
                // Check file pattern on microsoft windows
                if (strncmp(pattern, supported_globs[i], strlen(supported_globs[i])) == 0)
                {
                    // Add properties to the list
                    const char *name = g_file_info_get_display_name(info);
                    char *path = g_file_get_path(prefs1->file);
                    char *image_path = g_strdup_printf("%s/%s", path, name);
                    g_list_store_append(prefs1->images_list,
                                        my_item_new(name, image_path, FALSE));
                    g_free(path);
                    break;
                }
            }
            g_free(pattern);
        }
    }

    // Check weather list is updated
    if (g_list_model_get_n_items(G_LIST_MODEL(prefs1->images_list)) == 0)
    {
        prefs1->current_folder_index = -1;
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

static void update_internal_image(MyPrefs *prefs, const char **id)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_xpm_data(id);
    GdkPixbuf *sized = gdk_pixbuf_scale_simple(pixbuf, prefs->width,
                                               prefs->height, GDK_INTERP_BILINEAR);
    GdkTexture *texture = gdk_texture_new_for_pixbuf(pixbuf);
    gtk_picture_set_paintable(GTK_PICTURE(prefs->background), GDK_PAINTABLE(texture));
    // gtk_picture_set_pixbuf(GTK_PICTURE(prefs->background), pixbuf);
    g_object_unref(pixbuf);
    g_object_unref(sized);
}

static void update_external_image(MyPrefs *prefs, const char *file_name)
{
    GError *error = NULL;
    // Create a pixbuf
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(file_name, &error);
    if (error == NULL)
    {
        // Load the image with pixbuf
        GdkPixbuf *sized = gdk_pixbuf_scale_simple(pixbuf, prefs->width,
                                                   prefs->height, GDK_INTERP_BILINEAR);
        GdkTexture *texture = gdk_texture_new_for_pixbuf(pixbuf);
        gtk_picture_set_paintable(GTK_PICTURE(prefs->background), GDK_PAINTABLE(texture));
        // gtk_picture_set_pixbuf(GTK_PICTURE(prefs->background), sized);
        g_object_unref(sized);
        g_object_unref(pixbuf);
    }
    else
    {
        // if file load failed, load default image
        update_internal_image(prefs, winpe);
    }
}

static void file_dialog_opened(GObject *dialog, GAsyncResult *result, gpointer data)
{
    GFile *file;
    MyPrefs *prefs = MY_PREFS(data);

    // Get the file
    file = gtk_file_dialog_select_folder_finish(GTK_FILE_DIALOG(dialog), result, NULL);
    if (file != NULL)
    {
        // g_print("Dialog Accepted!");
        char *path = g_file_get_path(file);
        char *name = g_file_get_basename(file);
        g_list_store_append(prefs->folders_list,
                            my_item_new(name, path, FALSE));
        g_object_unref(file);
        g_free(path);
        g_free(name);
    }
    else
    {
        // g_print("Dialog Cancelled!");
    }
}

static void btnadd_clicked(GtkWidget *widget, MyPrefs *prefs)
{
    GtkFileDialog *dialog;
    // Create a file dialog
    dialog = gtk_file_dialog_new();
    gtk_file_dialog_select_folder(dialog, GTK_WINDOW(prefs), NULL, file_dialog_opened, prefs);
}

static void btnremove_clicked(GtkWidget *widget, MyPrefs *prefs)
{
}

// Scan the selection of two column views
static gboolean scan_func(gpointer data)
{
    MyPrefs *prefs = MY_PREFS(data);
    // Get the selection of folders view
    // The model and item of folders view
    auto folder_model = gtk_column_view_get_model(GTK_COLUMN_VIEW(prefs->folders_view));
    guint folder_item_index = gtk_single_selection_get_selected(GTK_SINGLE_SELECTION(folder_model));
    auto folder_item = gtk_single_selection_get_selected_item(GTK_SINGLE_SELECTION(folder_model));

    // File name and properties
    const char *folder_name = my_item_get_path(MY_ITEM(folder_item));
    gboolean is_internal = my_item_get_internal(MY_ITEM(folder_item));

    // Check weather the selection changed
    if (folder_item_index != prefs->current_folder_index || g_list_model_get_n_items(G_LIST_MODEL(prefs->images_list)) == 0)
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
            update_images_list(prefs);
            g_object_unref(prefs->file);
        }
        prefs->current_folder_index = folder_item_index;
        // Force reload image
        prefs->current_image_index = -1;
    }

    // Get the selection of images view
    // Check weather the list of images is empty
    if (g_list_model_get_n_items(G_LIST_MODEL(prefs->images_list)) == 0)
    {
        return TRUE;
    }

    // The model and item of images view
    auto model = gtk_column_view_get_model(GTK_COLUMN_VIEW(prefs->images_view));
    auto item = gtk_single_selection_get_selected_item(GTK_SINGLE_SELECTION(model));
    guint image_item_index = gtk_single_selection_get_selected(GTK_SINGLE_SELECTION(model));

    // File name and properties
    const char *file_name = my_item_get_path(MY_ITEM(item));
    is_internal = my_item_get_internal(MY_ITEM(item));

    // Check weather the selection changed
    if (image_item_index != prefs->current_image_index)
    {
        // Update image
        if (is_internal)
        {
            // For image which is internal
            switch (file_name[1])
            {
            case '1':
                update_internal_image(prefs, img7);
                break;
            case '2':
                update_internal_image(prefs, winpe);
                break;
            }
            prefs->current_image_index = image_item_index;
        }
        else
        {
            // For image which is outside
            update_external_image(prefs, file_name);
            prefs->current_image_index = image_item_index;
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

    // Default window size
    self->width = 1024;
    self->height = 576;

    // Default values to load the internal image
    self->current_folder_index = -1;
    self->current_image_index = -1;

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
    g_timeout_add(1, scan_func, self);

    // Connect signals
    g_signal_connect(self, "close-request", G_CALLBACK(my_prefs_close_request), NULL);
    g_signal_connect(self->btn_add, "clicked", G_CALLBACK(btnadd_clicked), self);
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
