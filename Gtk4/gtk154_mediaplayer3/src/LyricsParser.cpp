#include "MyItem.h"
#include "LyricsParser.h"
#include "MyMediaPlayer.h"
#include <cstdio>

#define lyrics_max_length 1024

static FILE *lyrics_file = NULL;
static gboolean line_read = FALSE, lyrics_updated = FALSE;
static char current_lyrics[lyrics_max_length];

static void get_substr(char *src, char *dest, size_t start,
                       size_t end)
{
    // Copy string to the end
    if (strlen(src) == 0 || strlen(src) == start + 1)
    {
        return;
    }
    for (int i = 0; i < end; i++)
    {
        dest[i] = src[i + start + 1];
    }
    dest[end] = '\0';
}

static size_t get_lrc_timestamp_end(const char *lrc_line)
{
    size_t timestamp_end;
    // Find the end of timestamp
    for (int i = 0; i < strlen(lrc_line); i++)
    {
        if (lrc_line[i] == ']')
        {
            timestamp_end = i;
        }
    }
    return timestamp_end;
}

static gint64 get_lrc_line_timestamp(const char *lyrics_line, size_t timestamp_length)
{
    static gint64 lyric_time = -1;
    // Minutes
    gint64 lyric_min = (lyrics_line[1] - '0') * 10 +
                       (lyrics_line[2] - '0');

    // Seconds
    gint64 lyric_sec = (lyrics_line[4] - '0') * 10 +
                       (lyrics_line[5] - '0');

    // Millseconds
    gint64 lyric_micro;
    switch (timestamp_length)
    {
    case 9:
        lyric_micro = (lyrics_line[7] - '0') * 100 +
                      (lyrics_line[8] - '0') * 10;
        break;
    case 10:
        lyric_micro = (lyrics_line[7] - '0') * 100 +
                      (lyrics_line[8] - '0') * 10 +
                      (lyrics_line[9] - '0');
        break;
    }

    if (lyric_micro > 500)
    {
        lyric_micro += 1000;
    }
    lyric_time = lyric_micro + lyric_sec * 1000 +
                 lyric_min * 60 * 1000;

    return lyric_time;
}

void update_lyrics(MyMediaPlayer *player)
{
    // Get position between filename and extension
    int point_pos;
    char *current_filename = my_media_player_get_filename(player);
    g_print("%s\n", current_filename);
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
    line_read = FALSE;
}

static void get_lyrics(gint64 curr_time, gboolean playing, MyMediaPlayer *player)
{
    char lyrics_line[lyrics_max_length];
    char label_string[lyrics_max_length];
    static size_t timestamp_length;
    static gint64 lyric_time;

    // g_print("%ld\n", curr_time);
    // Get lyrics data
    if (lyrics_file != NULL)
    {
        // g_print("Lrc file load successful\n");
        if (playing && !line_read)
        {
            // Get lyrics time
            fgets(lyrics_line, lyrics_max_length, lyrics_file);
            fflush(lyrics_file);

            // Some lrc files has empty lines
            if (strlen(lyrics_line) == 0)
            {
                line_read = TRUE;
                return;
            }

            // Not a number
            while (lyrics_line[1] < '0' || lyrics_line[1] > '9')
            {
                line_read = FALSE;
                return;
            }

            // Get timestamp length
            timestamp_length = get_lrc_timestamp_end(lyrics_line);

            g_print("%s\n", lyrics_line);
            lyric_time = get_lrc_line_timestamp(lyrics_line, timestamp_length);

            // Remove time stamp
            get_substr(lyrics_line, current_lyrics, timestamp_length,
                       strlen(lyrics_line) - timestamp_length);
            line_read = TRUE;
        }
        // g_print("%ld\n", lyric_time);

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

static gboolean get_media_playing(gint64 curr_time)
{
    static gint64 tmp_time = -1;
    if (curr_time == tmp_time)
    {
        return FALSE;
    }
    else
    {
        tmp_time = curr_time;
        return TRUE;
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

    if (get_media_playing(timestamp))
    {
        // Reset status when the media playing
        lyrics_updated = FALSE;
    }
    // g_print("%d\n", lyrics_updated);
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
