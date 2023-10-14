#pragma once

#include <gtk/gtk.h>

enum PlayMode{
    List_Once,          // Play the media with a playlist once
    List_Repeat,        // Play the media with a playlist repeatly
    List_Shuffle,       // Random play a media in the playlist
    One_Repeat          // Repeat a media file
    
};

G_DECLARE_FINAL_TYPE(MyMediaPlayer, my_media_player, MYMEDIA, PLAYER, GtkApplicationWindow)

gboolean my_media_player_get_music_loaded(MyMediaPlayer *self);

void my_media_player_set_music_loaded(MyMediaPlayer *self, gboolean music_loaded);

GtkWidget *my_media_player_get_video_widget(MyMediaPlayer *self);

GtkLabel *my_media_player_get_lyrics_widget(MyMediaPlayer *self);

PlayMode my_media_player_get_play_mode(MyMediaPlayer *self);

char *my_media_player_get_filename(MyMediaPlayer *self);

guint my_media_player_get_current_index(MyMediaPlayer *self);

guint my_media_player_get_n_audios(MyMediaPlayer *self);

void btnnext_clicked(GtkButton *self, MyMediaPlayer *player);

void my_media_player_load_random_audio(MyMediaPlayer *player);

void my_media_player_reload_audio(MyMediaPlayer *player);

MyMediaPlayer *my_media_player_new(GtkApplication *app);
