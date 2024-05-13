#pragma once

#include "MyMediaPlayer.h"

// Timeout function for music played time
gboolean lyric_time_func(gpointer data);

// Update lyrics file when a music will play
void load_lyrics(MyMediaPlayer *player);
