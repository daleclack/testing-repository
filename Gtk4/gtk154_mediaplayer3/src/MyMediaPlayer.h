#pragma once

#include <gtk/gtk.h>

enum PlayMode{
    List_Once,
    One_Repeat,
    List_Repeat
};

G_DECLARE_FINAL_TYPE(MyMediaPlayer, my_media_player, MYMEDIA, PLAYER, GtkApplicationWindow)

gboolean my_media_player_get_music_loaded(MyMediaPlayer *self);

void my_media_player_set_music_loaded(MyMediaPlayer *self, gboolean music_loaded);

GtkWidget *my_media_player_get_video_widget(MyMediaPlayer *self);

GtkLabel *my_media_player_get_lyrics_widget(MyMediaPlayer *self);

PlayMode my_media_player_get_play_mode(MyMediaPlayer *self);

char *my_media_player_get_filename(MyMediaPlayer *self);

MyMediaPlayer *my_media_player_new(GtkApplication *app);
