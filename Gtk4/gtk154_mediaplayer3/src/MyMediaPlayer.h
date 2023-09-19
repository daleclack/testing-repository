#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MyMediaPlayer, my_media_player, MYMEDIA, PLAYER, GtkApplicationWindow)

MyMediaPlayer *my_media_player_new(GtkApplication *app);
