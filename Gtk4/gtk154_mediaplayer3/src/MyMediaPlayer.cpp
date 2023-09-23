#include "MyMediaPlayer.h"
#include "MyItem.h"

struct _MyMediaPlayer
{
    GtkApplicationWindow parent_instance;
    GtkWidget *video, *label_lyrics;
    GtkWidget *main_box, *btn_box;
    GtkWidget *btn_add, *btn_remove;
    GtkWidget *btn_load, *btn_save;
    GtkWidget *column_view;
    GtkWidget *scrolled_window;
    GListStore *music_store;
    GtkSingleSelection *music_selection;
    GtkListItemFactory *filename_factory;
    GtkColumnViewColumn *filename_column;
};

G_DEFINE_TYPE(MyMediaPlayer, my_media_player, GTK_TYPE_APPLICATION_WINDOW)

void file_dialog_response(GObject *dialog, GAsyncResult *res, gpointer data)
{
    GFile *file;
    MyMediaPlayer *player = MYMEDIA_PLAYER(data);

    // Get file
    file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(dialog), res, NULL);
    if (file != NULL)
    {
        // Get file name
        char *path = g_file_get_path(file);
        char *name = g_file_get_basename(file);
        g_list_store_append(player->music_store,
                            my_item_new(name, path));
        g_object_unref(file);
        g_free(path);
        g_free(name);
    }
}

static void btnadd_clicked(GtkWidget *widget, MyMediaPlayer *player)
{
    // Create a file dialog window
    GtkFileDialog *dialog = gtk_file_dialog_new();

    // Open the file dialog
    gtk_file_dialog_open(dialog, GTK_WINDOW(player), NULL, file_dialog_response, player);
}

static void btnremove_clicked(GtkWidget *widget, MyMediaPlayer *player)
{
    // Get selected position
    guint pos = gtk_single_selection_get_selected(player->music_selection);

    // Remove the selected item
    g_list_store_remove(player->music_store, pos);
}

static void btnload_clicked(GtkWidget *widget, MyMediaPlayer *player)
{
}

static void btnsave_clicked(GtkWidget *widget, MyMediaPlayer *player)
{
}

static void column_view_activated(GtkColumnView *self, gint position, MyMediaPlayer *player)
{
    // Clear stream for player
    GtkMediaStream *stream = gtk_video_get_media_stream(GTK_VIDEO(player->video));
    if (stream != NULL)
    {
        gtk_media_file_clear(GTK_MEDIA_FILE(stream));
        // g_object_unref(stream);
    }

    // Play the selected media
    MyItem *item;
    GFile *music_file;
    item = MY_ITEM(gtk_single_selection_get_selected_item(player->music_selection));
    music_file = g_file_new_for_path(my_item_get_filename(item));
    if (music_file != NULL)
    {
        gtk_video_set_file(GTK_VIDEO(player->video), music_file);
        g_object_unref(music_file);
    }

    // // Check whether media stream has video
    // if(!gtk_media_stream_has_video(stream)){
    //     gtk_widget_set_size_request(player->video, 300, 50);
    // }
}

static void filename_factory_setup(GtkListItemFactory *factory,
                                   GtkListItem *item)
{
    // Create a label
    GtkWidget *label;
    label = gtk_label_new(" ");

    // Add the label to the item
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_list_item_set_child(item, label);
}

static void filename_factory_bind(GtkListItemFactory *factory,
                                  GtkListItem *item)
{
    // Get child
    GtkWidget *label;
    label = gtk_list_item_get_child(item);

    // Get item
    MyItem *file_item = MY_ITEM(gtk_list_item_get_item(item));
    gtk_label_set_label(GTK_LABEL(label),
                        my_item_get_dispname(file_item));
}

static void my_media_player_init(MyMediaPlayer *self)
{
    // Initalize window
    gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_title(GTK_WINDOW(self), "Gtk4 Media Player 3");
    gtk_window_set_default_size(GTK_WINDOW(self), 300, 400);

    // Create widgets
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->video = gtk_video_new();
    self->label_lyrics = gtk_label_new(" ");
    self->btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->btn_add = gtk_button_new_from_icon_name("list-add");
    self->scrolled_window = gtk_scrolled_window_new();
    self->btn_remove = gtk_button_new_from_icon_name("list-remove");
    self->btn_load = gtk_button_new_from_icon_name("go-up");
    self->btn_save = gtk_button_new_from_icon_name("document-save");
    gtk_widget_set_size_request(self->video, 300, 150);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->scrolled_window),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_label_set_markup(GTK_LABEL(self->label_lyrics),
                         "<span color=\"red\" size='12pt'>No Lyric File Found!</span>");

    // Link signals for buttons
    g_signal_connect(self->btn_add, "clicked", G_CALLBACK(btnadd_clicked), self);
    g_signal_connect(self->btn_remove, "clicked", G_CALLBACK(btnremove_clicked), self);
    g_signal_connect(self->btn_load, "clicked", G_CALLBACK(btnload_clicked), self);
    g_signal_connect(self->btn_save, "clicked", G_CALLBACK(btnsave_clicked), self);

    // Create store and list view
    self->music_store = g_list_store_new(MY_ITEM_TYPE);
    self->music_selection = gtk_single_selection_new(G_LIST_MODEL(self->music_store));
    self->column_view = gtk_column_view_new(GTK_SELECTION_MODEL(self->music_selection));
    gtk_widget_set_vexpand(self->column_view, TRUE);

    // Create factory for renderer
    self->filename_factory = gtk_signal_list_item_factory_new();
    self->filename_column = gtk_column_view_column_new("File Name",
                                                       self->filename_factory);
    g_signal_connect(self->filename_factory, "setup",
                     G_CALLBACK(filename_factory_setup), NULL);
    g_signal_connect(self->filename_factory, "bind",
                     G_CALLBACK(filename_factory_bind), NULL);
    g_signal_connect(self->column_view, "activate", G_CALLBACK(column_view_activated), self);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(self->column_view),
                                  self->filename_column);

    // Add widgets
    gtk_box_append(GTK_BOX(self->main_box), self->video);
    gtk_box_append(GTK_BOX(self->main_box), self->label_lyrics);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_add);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_remove);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_load);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_save);
    gtk_box_append(GTK_BOX(self->main_box), self->btn_box);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->scrolled_window),
                                  self->column_view);
    gtk_box_append(GTK_BOX(self->main_box), self->scrolled_window);
    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void my_media_player_class_init(MyMediaPlayerClass *klass)
{
}

MyMediaPlayer *my_media_player_new(GtkApplication *app)
{
    // Create a window for media player
    return MYMEDIA_PLAYER(g_object_new(my_media_player_get_type(),
                                       "application", app, NULL));
}
