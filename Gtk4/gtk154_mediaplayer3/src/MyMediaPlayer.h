#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MyMediaPlayer, my_media_player, MYMEDIA, PLAYER, GtkApplicationWindow)

gboolean my_media_player_get_music_loaded(MyMediaPlayer *self);

GtkWidget *my_media_player_get_video_widget(MyMediaPlayer *self);

GtkLabel *my_media_player_get_lyrics_widget(MyMediaPlayer *self);

char *my_media_player_get_filename(MyMediaPlayer *self);

MyMediaPlayer *my_media_player_new(GtkApplication *app);
