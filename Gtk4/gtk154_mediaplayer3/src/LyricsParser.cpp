#include "MyItem.h"
#include "LyricsParser.h"
#include "MyMediaPlayer.h"

#define lyrics_max_length 1024

static char *lyrics_content = NULL;
static gboolean lyrics_loaded = FALSE;
static gboolean line_read = FALSE, lyrics_updated = FALSE;
static char current_lyrics[lyrics_max_length];

// Get lyrics string
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

// Get the position of timestamp end to separate lyrics and timestamp
static size_t get_lrc_timestamp_end_pos(const char *lrc_line)
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

// Get timestamp of a lyrics line
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

    lyric_time = lyric_micro + lyric_sec * 1000 +
                 lyric_min * 60 * 1000;

    return lyric_time;
}

// Get a line of lyrics
static void get_lyrics_line(const char *lyrics, char *lyrics_line1, gboolean reset)
{
    static gint64 start_pos = 0, end_pos = 0;
    // Reset position to load from start, 
    // the lyrics and lyrics_line1 should be NULL to avoid problems
    if (reset)
    {
        start_pos = 0;
        end_pos = 0;
        return;
    }

    if (lyrics_loaded)
    {
        // Find the '\n'
        while (lyrics[end_pos] != '\n' && lyrics[end_pos] != '\0')
        {
            end_pos++;
        }

        // Copy contents
        for (int i = 0; i < end_pos - start_pos; i++)
        {
            lyrics_line1[i] = lyrics[i + start_pos];
        }
        lyrics_line1[end_pos - start_pos] = '\0';

        // Lyrics read finished
        if (lyrics[end_pos] == '\0')
        {
            end_pos = 0;
            lyrics_loaded = FALSE;
        }
        end_pos++;
        start_pos = end_pos;
    }
}

// Update lyrics
void update_lyrics(MyMediaPlayer *player)
{
    // Get position between filename and extension
    int point_pos;
    gsize length;
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

    // Load lyrics with gio to avoid coding problem
    GFile *lyrics_file = g_file_new_for_path(lyric_filename);

    // Refresh before load
    if (lyrics_content != NULL)
    {
        g_free(lyrics_content);
        lyrics_content = NULL;
    }

    // Load contents
    if (g_file_load_contents(lyrics_file, NULL, &lyrics_content, &length, NULL, NULL))
    {
        lyrics_loaded = TRUE;
    }
    else
    {
        lyrics_loaded = FALSE;
        return;
    }
    g_object_unref(lyrics_file);

    // Reset load status
    lyrics_updated = TRUE;
    line_read = FALSE;

    // Reset line read starts
    get_lyrics_line(NULL, NULL, TRUE);
}

// Get lyrics for a specfied time
static void get_lyrics(gint64 curr_time, gboolean playing, MyMediaPlayer *player)
{
    char lyrics_line[lyrics_max_length];
    char label_string[lyrics_max_length];
    static size_t timestamp_length;
    static gint64 lyric_time;

    // Get lyrics data
    if (lyrics_loaded)
    {
        // g_print("Lrc file load successful\n");
        if (playing && !line_read)
        {
            // Get lyrics line
            get_lyrics_line(lyrics_content, lyrics_line, FALSE);

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
            timestamp_length = get_lrc_timestamp_end_pos(lyrics_line);

            g_print("%s\n", lyrics_line);
            lyric_time = get_lrc_line_timestamp(lyrics_line, timestamp_length);

            // Remove time stamp
            get_substr(lyrics_line, current_lyrics, timestamp_length,
                       strlen(lyrics_line) - timestamp_length);
            line_read = TRUE;
        }
        if (curr_time >= lyric_time - 100 && curr_time <= lyric_time + 100 && 
         line_read || lyric_time == 0)
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
        // g_print("Lyric file open failed!\n");
        gtk_label_set_markup(my_media_player_get_lyrics_widget(player),
                             "<span color=\"red\" size='12pt'>No Lyric File Found!</span>");
    }
}

// Check whether the media is playing
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

// Check whether lyrics should be update
static void get_media_stream_status(MyMediaPlayer *player,
                                    GtkMediaStream *stream, gint64 timestamp)
{
    if (timestamp == 0 && !lyrics_updated)
    {
        // Load lyrics when a new media loaded
        update_lyrics(player);
    }

    if (get_media_playing(timestamp))
    {
        // Reset status when the media playing
        lyrics_updated = FALSE;
    }
}

// Time monitor
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
