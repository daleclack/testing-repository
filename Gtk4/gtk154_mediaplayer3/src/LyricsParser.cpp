#include "MyItem.h"
#include "LyricsParser.h"
#include "MyMediaPlayer.h"
#include <cstdio>
#include <cstring>

#define lyrics_max_length 1024

static FILE *lyrics_file = NULL;

void update_lyrics(MyMediaPlayer *player)
{
    // Get position between filename and extension
    int point_pos;
    char *current_filename = my_media_player_get_filename(player);
    for(int i = strlen(current_filename) - 1; i > 0; i--)
    {
        if(current_filename[i] == '.'){
            point_pos = i;
            break;
        }
    }

    // Get Lyrics file name
    char lyric_filename[path_max_length];
    strncpy(lyric_filename, current_filename, point_pos);
    strncat(lyric_filename, ".lrc", 4);

    // Open the lyrics file
    lyrics_file = fopen(lyric_filename, "r");
}

static void get_lyrics(gint64 curr_time, gboolean playing, MyMediaPlayer *player)
{
    char lyrics_line[lyrics_max_length];
    static gboolean line_read = FALSE;
    gint64 lyric_time = 0;
    // Get lyrics data
    if(lyrics_file != NULL)
    {
        if(playing && !line_read)
        {
            // Get lyrics time
            fgets(lyrics_line, lyrics_max_length, lyrics_file);
            gint64 lyric_min = (lyrics_line[1] - '0') * 10 + 
                (lyrics_line[2] - '0');
            gint64 lyric_sec = (lyrics_line[4] - '0') * 10 +
                (lyrics_line[5] - '0');
            lyric_time = (lyrics_line[7] - '0') * 100 +
                (lyrics_line[8] - '0') * 10 +
                (lyrics_line[9] - '0') +
                lyric_sec * 1000 +
                lyric_min * 1000 * 60;
            g_print("%lld\n", lyric_time);
            line_read = TRUE;
        }
    }else{
        gtk_label_set_markup(my_media_player_get_lyrics_widget(player),
            "<span color=\"red\" size='12pt'>No Lyric File Found!</span>");
    }
}

static void get_media_stream_status(GtkMediaStream *stream)
{
    if(gtk_media_stream_get_ended(stream))
    {
        fclose(lyrics_file);
        g_print("Media ended");
    }
}

gboolean lyric_time_func(gpointer data)
{
    MyMediaPlayer *player = MYMEDIA_PLAYER(data);
    // if music is loaded, try to get timestamp
    if (my_media_player_get_music_loaded(player))
    {
        // Get media stream
        GtkMediaStream *stream;
        stream = gtk_video_get_media_stream(GTK_VIDEO(
            my_media_player_get_video_widget(player)));

        // only get timestamp when media stream vaild
        if (GTK_IS_MEDIA_STREAM(stream))
        {
            // get timestamp
            gint64 timestamp = gtk_media_stream_get_timestamp(stream);
            gint64 timestamp_ms = timestamp / 1000;
            gboolean media_playing = gtk_media_stream_get_playing(stream);
            
            // Update lyrics
            get_lyrics(timestamp_ms, media_playing, player);

            // Check whether media stopped
            get_media_stream_status(stream);
        }
    }
    return TRUE;
}
