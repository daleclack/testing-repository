#include "MyItem.h"
#include "LyricsParser.h"
#include "MyMediaPlayer.h"

#define lyrics_max_length 1024

static char *lyrics_content = NULL;
static gboolean lyrics_loaded = FALSE;
static gboolean line_read = FALSE, lyrics_updated = FALSE;
static char current_lyrics[lyrics_max_length];
static gint64 lyric_time;

// Replace the symbol
static void UTF8_Replace_and_Symbol(gint64 pos_and_char, char *utf8_string)
{
    size_t string_length = strlen(utf8_string);

    // Copy string after '&'
    for (int i = pos_and_char + 1; i < string_length; i++)
    {
        utf8_string[i + 4] = utf8_string[i];
    }

    // Replace "&" with "&amp;"
    utf8_string[pos_and_char + 1] = 'a';
    utf8_string[pos_and_char + 2] = 'm';
    utf8_string[pos_and_char + 3] = 'p';
    utf8_string[pos_and_char + 4] = ';';

    // Fix end symbol
    utf8_string[string_length + 3] = '\0';
}

// Fix UTF-8 '&' String
static void UTF8_String_Fix(char *utf8_string)
{
    // Check for '&' String
    gint64 pos_and_char = -1;
    size_t string_length = strlen(utf8_string);
    for (int i = 0; i < string_length; i++)
    {
        if (utf8_string[i] == '&')
        {
            UTF8_Replace_and_Symbol(i, utf8_string);
        }
    }
}

// Get lyrics string
static void get_lrc_substr(char *src, char *dest,
                           size_t start, size_t end)
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
    static gint64 lyric_time_tmp = 0;
    // Minutes
    gint64 lyric_min = (lyrics_line[1] - '0') * 10 +
                       (lyrics_line[2] - '0');

    // Seconds
    gint64 lyric_sec = (lyrics_line[4] - '0') * 10 +
                       (lyrics_line[5] - '0');

    // Millseconds
    gint64 lyric_micro = 0;
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

    lyric_time_tmp = lyric_micro + lyric_sec * 1000 +
                     lyric_min * 60 * 1000;

    return lyric_time_tmp;
}

// Get a line of lyrics
static void get_lyrics_line(const char *lyrics, char *lyrics_line1, gboolean reset)
{
    static gint64 start_pos = 0, end_pos = 0;
    // Reset position to load frm start,
    // the lyrics and lyrics_line1 should be NULL to avoid problems
    if (reset)
    {
        start_pos = 0;
        end_pos = 0;
        return;
    }

    if (lyrics_loaded && lyrics)
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
            // lyrics_loaded = FALSE;
        }
        end_pos++;
        start_pos = end_pos;
    }
}

// Update lyrics
void load_lyrics(MyMediaPlayer *player)
{
    // Get position between filename and extension
    int point_pos;
    gsize length;
    char *current_filename = my_media_player_get_filename(player);
    // g_print("%s\n", current_filename);
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
    // g_print("%s\n", lyric_filename);

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

// Lyrics Line process
static void lyric_line_process(char *lyrics_line,
                               size_t &timestamp_length)
{
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

    // g_print("%s\n", lyrics_line);
    lyric_time = get_lrc_line_timestamp(lyrics_line, timestamp_length);

    // Remove time stamp
    get_lrc_substr(lyrics_line, current_lyrics, timestamp_length,
                   strlen(lyrics_line) - timestamp_length);

    // Fix some symbols
    UTF8_String_Fix(current_lyrics);

    // A lyric line is read
    line_read = TRUE;
}

// Update label that show lyrics
static void lyrics_label_update(gint64 &curr_time, MyMediaPlayer *player)
{
    char label_string[lyrics_max_length];
    char *color_str;

    // if time is on a lyrics, update the label
    if (curr_time >= lyric_time - 100 && curr_time <= lyric_time + 100 &&
            line_read ||
        lyric_time == 0)
    {
        // Since a new line is read and time match, load lyrics
        color_str = my_media_player_get_color(player);
        snprintf(label_string, lyrics_max_length,
                 "<span color=\"%s\" size='12pt'>%s</span>", color_str, current_lyrics);
        gtk_label_set_markup(my_media_player_get_lyrics_widget(player),
                             label_string);
        line_read = FALSE;
    }
    // free(color_str);
}

// Get lyrics for a specfied time
static void get_lyrics(gint64 curr_time, gboolean playing, MyMediaPlayer *player)
{
    char lyrics_line[lyrics_max_length];
    static size_t timestamp_length;

    // Get lyrics data
    if (lyrics_loaded)
    {
        // g_print("Lrc file load successful\n");
        if (playing && !line_read)
        {
            // Get lyrics line
            get_lyrics_line(lyrics_content, lyrics_line, FALSE);

            g_print("%s\n", lyrics_line);

            // Process lyrics line
            lyric_line_process(lyrics_line, timestamp_length);
        }
        // Try to update label
        lyrics_label_update(curr_time, player);
    }
    // else
    // {
    //     // g_print("Lyric file open failed!\n");
    //     gtk_label_set_markup(my_media_player_get_lyrics_widget(player),
    //                          "<span color=\"green\" size='12pt'>No Lyric File Found!</span>");
    // }
}

// Reset lyrics for drag of timeline
static void reset_lyrics(gint64 timestamp, GtkMediaStream *stream,
                         MyMediaPlayer *player)
{
    static size_t timestamp_length;
    lyric_time = -1;
    char lyrics_line[lyrics_max_length];
    char priv_lyrics_line[lyrics_max_length];

    // Reset loading status
    get_lyrics_line(NULL, NULL, TRUE);

    // Fine match lyrics line
    do
    {
        // Get Privous lyrics line
        strncpy(priv_lyrics_line, current_lyrics, lyrics_max_length);

        // Get lyrics line
        get_lyrics_line(lyrics_content, lyrics_line, FALSE);

        // Process lyrics line
        lyric_line_process(lyrics_line, timestamp_length);
    } while (lyric_time < timestamp);
    line_read = TRUE;

    // Show next lyrics
    char *label_string = g_strdup_printf("<span color=\"green\" size='12pt'>%s</span>",
                                         priv_lyrics_line);
    gtk_label_set_markup(my_media_player_get_lyrics_widget(player),
                         label_string);
    g_free(label_string);

    // Try to update label
    lyrics_label_update(timestamp, player);

    // Pause audio before seek to avoid isolation
    if (timestamp != 0)
    {
        gtk_media_stream_pause(stream);
        gtk_media_stream_seek(stream, timestamp * 1000);
        gtk_media_stream_play(stream);
    }
}

// Check whether the media is playing
static gboolean get_media_playing(gint64 curr_time,
                                  GtkMediaStream *stream, MyMediaPlayer *player)
{
    static gint64 tmp_time = -1;
    if (curr_time == tmp_time)
    {
        return FALSE;
    }
    else
    {
        gint64 delta_time = abs(curr_time - tmp_time);
        if (delta_time > 500)
        {
            // Reset lyrics load status
            reset_lyrics(curr_time, stream, player);
        }
        tmp_time = curr_time;
        return TRUE;
    }
}

// Check whether lyrics should be update
static gboolean get_media_stream_status(MyMediaPlayer *player,
                                        GtkMediaStream *stream, gint64 timestamp)
{
    if (timestamp == 0 && !lyrics_updated && !lyrics_loaded)
    {
        // Load lyrics when a new media loaded
        load_lyrics(player);
    }

    if (get_media_playing(timestamp, stream, player))
    {
        // Reset status when the media playing
        lyrics_updated = FALSE;
        lyrics_loaded = TRUE;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    return FALSE;
}

// Operations when a media play end
static void media_play_ended_handler(MyMediaPlayer *player)
{
    GtkMediaStream *stream;

    // Get Current Play mode
    PlayMode play_mode = my_media_player_get_play_mode(player);

    switch (play_mode)
    {
    // Play a list of music once
    // g_print("%d", play_mode);
    case PlayMode::List_Once:
        // Only play music when current audio is not the end of the audio list
        // g_print("%d %d\n", my_media_player_get_current_index(player),
        //         my_media_player_get_n_audios(player));
        if (my_media_player_get_current_index(player) <
            my_media_player_get_n_audios(player) - 1)
        {
            // use the function for play next button to load next audio
            btnnext_clicked(NULL, player);

            // Get media stream to control
            stream = gtk_video_get_media_stream(GTK_VIDEO(
                my_media_player_get_video_widget(player)));

            // Play media stream associated with media file
            gtk_media_stream_play(stream);
        }
        break;
    case PlayMode::List_Repeat:
        // In List Repeat Mode, use the function for play next button
        btnnext_clicked(NULL, player);

        // Get Media stream to control
        stream = gtk_video_get_media_stream(GTK_VIDEO(
            my_media_player_get_video_widget(player)));

        // Play media stream associated with media file
        gtk_media_stream_play(stream);
        break;
    case PlayMode::List_Shuffle:
        // Play music with random index
        my_media_player_load_random_audio(player);

        // Get Media stream to control
        stream = gtk_video_get_media_stream(GTK_VIDEO(
            my_media_player_get_video_widget(player)));

        // Play media stream associated with media file
        gtk_media_stream_play(stream);
        break;
    case PlayMode::One_Repeat:
        // Reload audio
        my_media_player_reload_audio(player);

        // Get media stream to control
        stream = gtk_video_get_media_stream(GTK_VIDEO(
            my_media_player_get_video_widget(player)));

        // Play media stream associated with media file
        gtk_media_stream_play(stream);

        break;
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

            // Update lyrics and Check whether media stopped
            get_lyrics(timestamp_ms, get_media_stream_status(player, stream, timestamp_ms),
                       player);

            // The Media ended, reset the status
            if (gtk_media_stream_get_ended(stream) &&
                my_media_player_get_music_loaded(player))
            {
                my_media_player_set_music_loaded(player, FALSE);
                media_play_ended_handler(player);
            }
        }
    }
    return TRUE;
}
