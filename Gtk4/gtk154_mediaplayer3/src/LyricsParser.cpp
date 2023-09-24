#include "MyItem.h"
#include "LyricsParser.h"
#include "MyMediaPlayer.h"
#include <cstdio>
#include <cstring>

#define lyrics_max_length 1024
#define timestamp_length 12

static FILE *lyrics_file = NULL;
static gboolean line_read = FALSE, lyrics_updated = FALSE;
static char current_lyrics[lyrics_max_length];


void update_lyrics(MyMediaPlayer *player)
{
    // Get position between filename and extension
    int point_pos;
    char *current_filename = my_media_player_get_filename(player);
    for (int i = strlen(current_filename) - 1; i > 0; i--)
    {
        if (current_filename[i] == '.')
        {
            point_pos = i;
            break;
        }
    }

    // Get Lyrics file name
    char lyric_filename[path_max_length];
    strncpy(lyric_filename, current_filename, point_pos);
    lyric_filename[point_pos] = '\0';
    strncat(lyric_filename, ".lrc", 4);
    g_print("%s\n", lyric_filename);

    // Close pervious opened lyrics file
    if (lyrics_file != NULL)
    {
        fclose(lyrics_file);
        lyrics_file = NULL;
    }

    // Open the lyrics file
    lyrics_file = fopen(lyric_filename, "rt+");
    lyrics_updated = TRUE;
}

static void get_substr(char *src, char *dest, size_t start, size_t end)
{
    // Copy string to the end
    if(strlen(src) == 0)
    {
        return ;
    }
    for (int i = 0; i < end; i++)
    {
        dest[i] = src[i + start];
    }
    dest[end] = '\0';
}

static void get_lyrics(gint64 curr_time, gboolean playing, MyMediaPlayer *player)
{
    char lyrics_line[lyrics_max_length];
    char label_string[lyrics_max_length];
    static gint64 lyric_time = -1;

    // g_print("%ld\n", curr_time);
    // Get lyrics data
    if (lyrics_file != NULL)
    {
        if (playing && !line_read)
        {
            // Get lyrics time
            fgets(lyrics_line, lyrics_max_length, lyrics_file);
            fflush(lyrics_file);
            // g_print("%s\n", lyrics_line);
            gint64 lyric_min = (lyrics_line[1] - '0') * 10 +
                               (lyrics_line[2] - '0');
            gint64 lyric_sec = (lyrics_line[4] - '0') * 10 +
                               (lyrics_line[5] - '0');
            lyric_time = (lyrics_line[7] - '0') * 100 +
                         (lyrics_line[8] - '0') * 10 +
                         (lyrics_line[9] - '0') +
                         lyric_sec * 1000 +
                         lyric_min * 1000 * 60;

            // Remove time stamp
            get_substr(lyrics_line, current_lyrics, timestamp_length,
                       strlen(lyrics_line) - timestamp_length);
            line_read = TRUE;
        }
        
        if (curr_time / 100 == lyric_time / 100 && line_read || lyric_time == 0)
        {
            // Since a new line is read and time match, load lyrics
            snprintf(label_string, lyrics_max_length,
                     "<span color=\"green\" size='12pt'>%s</span>", current_lyrics);
            gtk_label_set_markup(my_media_player_get_lyrics_widget(player),
                                 label_string);
            line_read = FALSE;
        }
    }
    else
    {
        gtk_label_set_markup(my_media_player_get_lyrics_widget(player),
                             "<span color=\"red\" size='12pt'>No Lyric File Found!</span>");
    }
}

static void get_media_stream_status(MyMediaPlayer *player,
                                    GtkMediaStream *stream, gint64 timestamp)
{
    if (timestamp == 0 && !lyrics_updated)
    {
        // Load lyrics when a new media loaded
        // g_print("Load new lyrics\n");
        update_lyrics(player);
    }

    if (timestamp == 1)
    {
        // Reset status when the media playing
        lyrics_updated = FALSE;
    }
}

gboolean get_media_playing(gint64 curr_time)
{
    static gint64 tmp_time = -1;
    if(curr_time == tmp_time){
        return FALSE;
    }else{
        tmp_time = curr_time;
        return TRUE;
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
            // g_print("%ld\n", timestamp_ms);

            // Update lyrics
            get_lyrics(timestamp_ms, get_media_playing(timestamp), player);

            // Check whether media stopped
            get_media_stream_status(player, stream, timestamp_ms);
        }
    }
    return TRUE;
}
