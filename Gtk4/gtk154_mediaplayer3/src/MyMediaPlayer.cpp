#include "MyMediaPlayer.h"
#include "LyricsParser.h"
#include "MyItem.h"
#include "../json_nlohmann/json.hpp"
#include <vector>
#include <fstream>
#include <cstring>

using json = nlohmann::json;
typedef std::vector<std::string> string_vector;

struct _MyMediaPlayer
{
    GtkApplicationWindow parent_instance;
    GtkWidget *video, *label_lyrics;
    GtkWidget *ctrl_box;
    GtkWidget *btn_priv, *btn_play, *btn_next,
        *btn_stop, *btn_playmode;
    PlayMode current_play_mode;
    GtkWidget *main_box, *btn_box;
    GtkWidget *btn_add, *btn_remove;
    GtkWidget *btn_load, *btn_save;
    GtkWidget *list_expander, *list_box;
    GtkWidget *btn_color;
    GtkColorDialog *dialog_color;
    GtkWidget *column_view;
    GtkWidget *scrolled_window, *scrolled_lyrics;
    GListStore *music_store;
    char current_filename[path_max_length];
    guint n_items, current_audio_index;
    gboolean music_loaded;
    gboolean dark_mode;
    GtkSingleSelection *music_selection;
    GtkListItemFactory *filename_factory;
    GtkColumnViewColumn *filename_column;
};

G_DEFINE_TYPE(MyMediaPlayer, my_media_player, GTK_TYPE_APPLICATION_WINDOW)

// Add media file item to the list when the file open dialog accepted
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

        // Update items count of media files
        player->n_items = g_list_model_get_n_items(
            G_LIST_MODEL(player->music_store));
        // Update index information
        player->current_audio_index = gtk_single_selection_get_selected(
            player->music_selection);
    }
}

// Add a media file item
static void btnadd_clicked(GtkWidget *widget, MyMediaPlayer *player)
{
    // Create a file dialog window
    GtkFileDialog *dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_title(dialog, "Open media file");

    // Open the file dialog
    gtk_file_dialog_open(dialog, GTK_WINDOW(player), NULL, file_dialog_response, player);
}

// Remove the selected item
static void btnremove_clicked(GtkWidget *widget, MyMediaPlayer *player)
{
    // Get selected position
    guint pos = gtk_single_selection_get_selected(player->music_selection);

    // Remove the selected item
    g_list_store_remove(player->music_store, pos);

    // Update index information
    player->n_items = g_list_model_get_n_items(
        G_LIST_MODEL(player->music_store));
    player->current_audio_index = gtk_single_selection_get_selected(
        player->music_selection);
}

// Load playlist
static void load_playlist(std::string filename, MyMediaPlayer *player)
{
    // Load a new json data to the list
    std::fstream infile;

    infile.open(filename, std::ios_base::in);
    if (infile.is_open())
    {
        // Get json data
        json data = json::parse(infile);

        // Check whether json data is empty
        if (data.empty())
        {
            return;
        }
        try
        {
            string_vector sound_names = data["name"];
            string_vector sound_paths = data["path"];
            std::string disp_name, file_path;

            for (int i = 0; i < sound_names.size(); i++)
            {
                // Append items
                disp_name = sound_names[i];
                file_path = sound_paths[i];
                g_list_store_append(G_LIST_STORE(player->music_store),
                                    my_item_new(disp_name.c_str(), file_path.c_str()));
            }
        }
        catch (const nlohmann::detail::exception &ex)
        {
            g_print("%s\n", ex.what());
        }

        // Update count of media files
        player->n_items = g_list_model_get_n_items(
            G_LIST_MODEL(player->music_store));
        // Update index information
        player->current_audio_index = gtk_single_selection_get_selected(
            player->music_selection);
    }
}

// Response for the dialog of load playlist
static void load_dialog_response(GObject *dialog, GAsyncResult *res, gpointer data)
{
    GFile *file;
    MyMediaPlayer *player = MYMEDIA_PLAYER(data);

    // Get file
    file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(dialog), res, NULL);
    if (file != NULL)
    {
        // Get file name
        char *path = g_file_get_path(file);
        load_playlist(path, player);
        g_object_unref(file);
    }
}

// Handler for load playlist button
static void btnload_clicked(GtkWidget *widget, MyMediaPlayer *player)
{
    // Create a file dialog window
    GtkFileDialog *dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_title(dialog, "Open Playlist file");

    // Create a filter
    GtkFileFilter *filter_json = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter_json, "*.json");
    gtk_file_filter_set_name(filter_json, "json file");

    // Create store for filters
    GListStore *filters_store = g_list_store_new(GTK_TYPE_FILE_FILTER);
    g_list_store_append(filters_store, filter_json);
    gtk_file_dialog_set_filters(dialog, G_LIST_MODEL(filters_store));

    // Set json filter for default
    gtk_file_dialog_set_default_filter(dialog, filter_json);

    // Open the file dialog
    gtk_file_dialog_open(dialog, GTK_WINDOW(player), NULL, load_dialog_response, player);
}

// Save the play list to a path
static void save_playlist(std::string filename, MyMediaPlayer *player)
{
    // Save playlist to json data
    string_vector sound_names, sound_paths;
    std::string disp_name, file_path;

    // Get n items of the list
    guint list_items = g_list_model_get_n_items(G_LIST_MODEL(player->music_store));

    // Insert all items to the vectors
    for (int i = 0; i < list_items; i++)
    {
        // Get sound name and the path
        MyItem *item = MY_ITEM(g_list_model_get_item(G_LIST_MODEL(player->music_store), i));
        disp_name = std::string(my_item_get_dispname(item));
        file_path = std::string(my_item_get_filename(item));

        // Push data to the vectors
        sound_names.push_back(disp_name);
        sound_paths.push_back(file_path);
    }

    // Save data to json file
    std::fstream outfile;
    outfile.open(filename, std::ios::out);
    if (outfile.is_open())
    {
        // Load json data
        json data = json::parse(R"(
            {
                "name":[""],
                "path":[""]
            }
        )");
        data["name"] = sound_names;
        data["path"] = sound_paths;

        // Save to file
        outfile << data;
    }
    else
    {
        g_print("Failed to save file!\n");
    }
    outfile.close();
}

// Handler for save list dialog
static void btnsave_clicked(GtkWidget *widget, MyMediaPlayer *player)
{
    // Currently just save the playlist to a default name
    save_playlist("playlist.json", player);
}

// Load a audio with specificed index
static void load_audio(MyItem *item, MyMediaPlayer *player)
{
    // Load the audio file
    GFile *music_file;
    const char *file_name, *disp_name;

    file_name = my_item_get_filename(item);
    music_file = g_file_new_for_path(file_name);
    disp_name = my_item_get_dispname(item);
    if (music_file != NULL)
    {
        // Add file to video widget for play
        gtk_video_set_file(GTK_VIDEO(player->video), music_file);

        // Mark the player is ready and update current file name
        player->music_loaded = TRUE;
        char *filename1 = player->current_filename;
        strncpy(filename1, file_name, strlen(file_name));
        filename1[strlen(file_name)] = '\0';
        g_object_unref(music_file);

        // Set the label for initial status
        char *label_str = g_strdup_printf("<span color=\"green\" size='12pt'>%s</span>", disp_name);
        gtk_label_set_markup(GTK_LABEL(player->label_lyrics), label_str);
        g_free(label_str);

        // Force update lyrics file
        load_lyrics(player);

        // Enable control button
        gtk_widget_set_sensitive(player->btn_play, TRUE);
    }
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
    gtk_video_set_file(GTK_VIDEO(player->video), NULL);

    // Play the selected media
    MyItem *item;

    // Get selection and open the music file
    item = MY_ITEM(gtk_single_selection_get_selected_item(player->music_selection));
    load_audio(item, player);

    // Update Column index
    player->current_audio_index = gtk_single_selection_get_selected(player->music_selection);
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

gboolean my_media_player_get_music_loaded(MyMediaPlayer *self)
{
    // Get whether music is loaded
    return self->music_loaded;
}

void my_media_player_set_music_loaded(MyMediaPlayer *self, gboolean music_loaded)
{
    // Set status of music loaded
    self->music_loaded = music_loaded;
}

GtkWidget *my_media_player_get_video_widget(MyMediaPlayer *self)
{
    // Get video widget
    return self->video;
}

GtkLabel *my_media_player_get_lyrics_widget(MyMediaPlayer *self)
{
    // Get Label for lyrics
    return GTK_LABEL(self->label_lyrics);
}

char *my_media_player_get_filename(MyMediaPlayer *self)
{
    // Get file name
    return self->current_filename;
}

PlayMode my_media_player_get_play_mode(MyMediaPlayer *self)
{
    // Get Current play mode
    return self->current_play_mode;
}

guint my_media_player_get_current_index(MyMediaPlayer *self)
{
    // Get the index of current playing audio
    return self->current_audio_index;
}

guint my_media_player_get_n_audios(MyMediaPlayer *self)
{
    // Get the number of audios in the list
    return self->n_items;
}

static void my_media_player_expander_activate(GtkExpander *self, MyMediaPlayer *player)
{
    if (!gtk_expander_get_expanded(self))
    {
        g_print("Try to recover size!\n");
        gtk_widget_set_size_request(player->main_box, 300, 270);
        gtk_widget_set_size_request(GTK_WIDGET(player), 300, 270);
        gtk_widget_queue_resize(player->list_box);
        gtk_widget_queue_resize(GTK_WIDGET(player));
    }
}

// Create a button with dark icon support
static GtkWidget *player_button_new(const char *icon_name, gboolean dark_mode)
{
    char *icon_name1;
    GtkWidget *button;
    //  Change icon name string for dark mode
    if (dark_mode)
    {
        icon_name1 = g_strdup_printf("%s-dark", icon_name);
    }
    else
    {
        icon_name1 = g_strdup_printf("%s", icon_name);
    }

    // Set icon name and free memory for icon name
    button = gtk_button_new_from_icon_name(icon_name1);
    g_free(icon_name1);
    return button;
}

// Set button icon name with dark icon theme support
static void player_button_set_icon_name(GtkButton *button, const char *icon_name,
                                        gboolean dark_mode)
{
    char *icon_name1;
    //  Change icon name string for dark mode
    if (dark_mode)
    {
        icon_name1 = g_strdup_printf("%s-dark", icon_name);
    }
    else
    {
        icon_name1 = g_strdup_printf("%s", icon_name);
    }

    // Set icon name and free memory for icon name
    gtk_button_set_icon_name(button, icon_name1);
    g_free(icon_name1);
}

// Play button
static void btnplay_clicked(GtkButton *self, MyMediaPlayer *player)
{
    // Get Media stream and play
    GtkMediaStream *stream = gtk_video_get_media_stream(GTK_VIDEO(player->video));
    if (GTK_IS_MEDIA_STREAM(stream))
    {
        if (gtk_media_stream_get_playing(stream))
        {
            // Media is playing, pause it
            gtk_media_stream_pause(stream);
            player_button_set_icon_name(self, "media-playback-start", player->dark_mode);
        }
        else
        {
            // Media is not playing
            gtk_media_stream_play(stream);
            player_button_set_icon_name(self, "media-playback-pause", player->dark_mode);
        }
    }
}

// Play previous music
static void btnpriv_clicked(GtkButton *self, MyMediaPlayer *player)
{
    // Clear stream for player
    GtkMediaStream *stream = gtk_video_get_media_stream(GTK_VIDEO(player->video));
    if (stream != NULL)
    {
        gtk_media_file_clear(GTK_MEDIA_FILE(stream));
        // g_object_unref(stream);
    }

    // Clear video widget
    gtk_video_set_file(GTK_VIDEO(player->video), NULL);

    // Current index
    if (player->current_audio_index == 0)
    {
        player->current_audio_index = player->n_items - 1;
    }
    else
    {
        player->current_audio_index -= 1;
    }

    // Load music at index
    // Get item
    MyItem *item = MY_ITEM(g_list_model_get_item(G_LIST_MODEL(player->music_store),
                                                 player->current_audio_index));
    load_audio(item, player);

    // Update selected item
    gtk_single_selection_set_selected(player->music_selection,
                                      player->current_audio_index);
}

// Play next music
void btnnext_clicked(GtkButton *self, MyMediaPlayer *player)
{
    // Clear stream for player
    GtkMediaStream *stream = gtk_video_get_media_stream(GTK_VIDEO(player->video));
    if (stream != NULL)
    {
        gtk_media_file_clear(GTK_MEDIA_FILE(stream));
        // g_object_unref(stream);
    }

    // Clear video widget
    gtk_video_set_file(GTK_VIDEO(player->video), NULL);

    // Current index
    if (player->current_audio_index == (player->n_items - 1))
    {
        player->current_audio_index = 0;
    }
    else
    {
        player->current_audio_index += 1;
    }

    // Load music at index
    // Get item
    MyItem *item = MY_ITEM(g_list_model_get_item(G_LIST_MODEL(player->music_store),
                                                 player->current_audio_index));
    load_audio(item, player);

    // Update selected item
    gtk_single_selection_set_selected(player->music_selection,
                                      player->current_audio_index);
}

// Load music with random index
void my_media_player_load_random_audio(MyMediaPlayer *player)
{
    // Get music index
    player->current_audio_index = rand() % (player->n_items);

    // Clear stream for player
    GtkMediaStream *stream = gtk_video_get_media_stream(GTK_VIDEO(player->video));
    if (stream != NULL)
    {
        gtk_media_file_clear(GTK_MEDIA_FILE(stream));
        // g_object_unref(stream);
    }

    // Clear video widget
    gtk_video_set_file(GTK_VIDEO(player->video), NULL);

    // Load music at index
    // Get item
    MyItem *item = MY_ITEM(g_list_model_get_item(G_LIST_MODEL(player->music_store),
                                                 player->current_audio_index));
    load_audio(item, player);

    // Update selected item
    gtk_single_selection_set_selected(player->music_selection,
                                      player->current_audio_index);
}

// Reload audio for repeat mode
void my_media_player_reload_audio(MyMediaPlayer *player)
{
    // Clear stream for player
    GtkMediaStream *stream = gtk_video_get_media_stream(GTK_VIDEO(player->video));
    if (stream != NULL)
    {
        gtk_media_file_clear(GTK_MEDIA_FILE(stream));
        // g_object_unref(stream);
    }

    // Clear video widget
    gtk_video_set_file(GTK_VIDEO(player->video), NULL);

    // Load music at index
    // Get item
    MyItem *item = MY_ITEM(g_list_model_get_item(G_LIST_MODEL(player->music_store),
                                                 player->current_audio_index));
    load_audio(item, player);

    // Update selected item
    gtk_single_selection_set_selected(player->music_selection,
                                      player->current_audio_index);
}

// Stop current music
static void btnstop_clicked(GtkButton *self, MyMediaPlayer *player)
{
    // Get Media stream and stop
    GtkMediaStream *stream = gtk_video_get_media_stream(GTK_VIDEO(player->video));
    gtk_media_file_clear(GTK_MEDIA_FILE(stream));
    gtk_video_set_file(GTK_VIDEO(player->video), NULL);
    player_button_set_icon_name(GTK_BUTTON(player->btn_play), "media-playback-start",
                                player->dark_mode);
    gtk_widget_set_sensitive(player->btn_play, FALSE);
}

// Switch play mode
static void btn_playmode_clicked(GtkButton *self, MyMediaPlayer *player)
{
    // Change play mode
    switch (player->current_play_mode)
    {
    case PlayMode::List_Once:
        player->current_play_mode = PlayMode::List_Repeat;
        player_button_set_icon_name(self, "media-playlist-repeat", player->dark_mode);
        break;
    case PlayMode::List_Repeat:
        player->current_play_mode = PlayMode::List_Shuffle;
        player_button_set_icon_name(self, "media-playlist-shuffle", player->dark_mode);
        break;
    case PlayMode::List_Shuffle:
        player->current_play_mode = PlayMode::One_Repeat;
        player_button_set_icon_name(self, "media-playlist-repeat-one", player->dark_mode);
        break;
    case PlayMode::One_Repeat:
        player->current_play_mode = PlayMode::List_Once;
        player_button_set_icon_name(self, "media-playlist-normal", player->dark_mode);
        break;
    }
}

static gboolean my_media_player_close_request(GtkWindow *window)
{
    // Save current list to a playlist file
    save_playlist("playlist.json", MYMEDIA_PLAYER(window));
    gtk_window_destroy(window);
    return TRUE;
}

// Get whether use dark icon theme, to match icons with stack icons
static gboolean my_media_player_check_dark_theme(MyMediaPlayer *player)
{
    gboolean dark_mode = FALSE;
    int theme_name_index = 0, theme_name_length;
    char temp_string[5] = {0};
    // Get current theme
    GtkIconTheme *theme = gtk_icon_theme_get_for_display(
        gtk_widget_get_display(GTK_WIDGET(player)));
    char *theme_name = gtk_icon_theme_get_theme_name(theme);
    theme_name_length = strlen(theme_name);

    // Translate string to lower
    for (int i = 0; i < theme_name_length; i++)
    {
        theme_name[i] = tolower(theme_name[i]);
    }

    // Check "dark" string
    for (int i = 0; i < 4; i++)
    {
        temp_string[i] = theme_name[theme_name_length - 4 + i];
    }

    if (strncmp(temp_string, "dark", 4) == 0)
    {
        dark_mode = TRUE;
    }
    free(theme_name);

    return dark_mode;
}

char *my_media_player_get_color(MyMediaPlayer *player)
{
    const GdkRGBA *color_rgba;
    color_rgba = gtk_color_dialog_button_get_rgba(
        GTK_COLOR_DIALOG_BUTTON(player->btn_color));
    char *color_str = g_strdup_printf("#%02X%02X%02X",
                                      (int)(color_rgba->red * 256),
                                      (int)(color_rgba->green * 256),
                                      (int)(color_rgba->blue * 256));
    return color_str;
}

static void my_media_player_init(MyMediaPlayer *self)
{
    // Initalize window
    gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_title(GTK_WINDOW(self), "Gtk4 Media Player 3");
    gtk_window_set_default_size(GTK_WINDOW(self), 300, 270);
    gtk_window_set_resizable(GTK_WINDOW(self), TRUE);

    // Check whether use dark icon name
    self->dark_mode = my_media_player_check_dark_theme(self);

    // Create widgets
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->video = gtk_video_new();
    self->label_lyrics = gtk_label_new(" ");
    self->ctrl_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->btn_play = player_button_new("media-playback-start", self->dark_mode);
    self->btn_priv = player_button_new("media-skip-backward", self->dark_mode);
    self->btn_next = player_button_new("media-skip-forward", self->dark_mode);
    self->btn_stop = player_button_new("media-playback-stop", self->dark_mode);
    self->btn_playmode = player_button_new("media-playlist-repeat", self->dark_mode);
    self->dialog_color = gtk_color_dialog_new();
    self->btn_color = gtk_color_dialog_button_new(self->dialog_color);
    self->btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->btn_add = gtk_button_new_from_icon_name("list-add");
    self->scrolled_window = gtk_scrolled_window_new();
    self->scrolled_lyrics = gtk_scrolled_window_new();
    self->list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->list_expander = gtk_expander_new("Play List");
    self->btn_remove = gtk_button_new_from_icon_name("list-remove");
    self->btn_load = gtk_button_new_from_icon_name("go-up");
    self->btn_save = gtk_button_new_from_icon_name("document-save");

    // Initalize widgets
    gtk_widget_set_size_request(self->video, 300, 150);
    gtk_widget_set_halign(self->ctrl_box, GTK_ALIGN_CENTER);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->scrolled_window),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    // gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->scrolled_window),
    //                                GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
    gtk_label_set_markup(GTK_LABEL(self->label_lyrics),
                         "<span color=\"red\" size='12pt'>No media file playing!</span>");
    gtk_video_set_autoplay(GTK_VIDEO(self->video), FALSE);
    gtk_widget_set_hexpand(self->main_box, TRUE);
    gtk_widget_set_vexpand(self->main_box, TRUE);

    // Link signals for buttons
    g_signal_connect(self->btn_add, "clicked", G_CALLBACK(btnadd_clicked), self);
    g_signal_connect(self->btn_remove, "clicked", G_CALLBACK(btnremove_clicked), self);
    g_signal_connect(self->btn_load, "clicked", G_CALLBACK(btnload_clicked), self);
    g_signal_connect(self->btn_save, "clicked", G_CALLBACK(btnsave_clicked), self);
    g_signal_connect(self->list_expander, "activate",
                     G_CALLBACK(my_media_player_expander_activate), self);
    g_signal_connect(self->btn_play, "clicked", G_CALLBACK(btnplay_clicked), self);
    g_signal_connect(self->btn_priv, "clicked", G_CALLBACK(btnpriv_clicked), self);
    g_signal_connect(self->btn_next, "clicked", G_CALLBACK(btnnext_clicked), self);
    g_signal_connect(self->btn_stop, "clicked", G_CALLBACK(btnstop_clicked), self);
    g_signal_connect(self->btn_playmode, "clicked",
                     G_CALLBACK(btn_playmode_clicked), self);

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
    gtk_widget_set_size_request(self->column_view, 300, 250);

    // Add a timer for music playing
    self->music_loaded = FALSE;
    g_timeout_add(1, lyric_time_func, self);

    // Load a default playlist
    load_playlist("playlist.json", self);

    // Default Play mode is List_Repeat mode
    self->current_play_mode = PlayMode::List_Repeat;

    // Add widgets
    gtk_box_append(GTK_BOX(self->main_box), self->video);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->scrolled_lyrics),
                                  self->label_lyrics);
    gtk_box_append(GTK_BOX(self->main_box), self->scrolled_lyrics);
    gtk_box_append(GTK_BOX(self->ctrl_box), self->btn_priv);
    gtk_box_append(GTK_BOX(self->ctrl_box), self->btn_play);
    gtk_box_append(GTK_BOX(self->ctrl_box), self->btn_next);
    gtk_box_append(GTK_BOX(self->ctrl_box), self->btn_stop);
    gtk_box_append(GTK_BOX(self->ctrl_box), self->btn_playmode);
    gtk_box_append(GTK_BOX(self->ctrl_box), self->btn_color);
    gtk_box_append(GTK_BOX(self->main_box), self->ctrl_box);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_add);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_remove);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_load);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_save);
    gtk_box_append(GTK_BOX(self->list_box), self->btn_box);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->scrolled_window),
                                  self->column_view);
    gtk_box_append(GTK_BOX(self->list_box), self->scrolled_window);
    gtk_expander_set_child(GTK_EXPANDER(self->list_expander), self->list_box);
    gtk_box_append(GTK_BOX(self->main_box), self->list_expander);
    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void my_media_player_class_init(MyMediaPlayerClass *klass)
{
    GTK_WINDOW_CLASS(klass)->close_request = my_media_player_close_request;
}

MyMediaPlayer *my_media_player_new(GtkApplication *app)
{
    // Create a window for media player
    return MYMEDIA_PLAYER(g_object_new(my_media_player_get_type(),
                                       "application", app, NULL));
}
