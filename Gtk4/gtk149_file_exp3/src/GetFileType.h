/*
Patch for Microsoft Windows
*/
#pragma once

#include <gtk/gtk.h>
#include <cstring>

// Check the whether the selected file is directory
static inline gboolean check_directory(GFileInfo *info)
{
#ifdef _WIN32
    // Since all files for windows will be "unknown" type, 
    // use content type to check file.
    const char *file_type = g_file_info_get_content_type(info);
    if(strncmp(file_type, "inode/directory", strlen("inode/directory")) == 0)
    {
        return TRUE;
    }
#else
    if(g_file_info_get_file_type(info) == G_FILE_TYPE_DIRECTORY){
        return TRUE;
    }
#endif
    // Not a directory, return FALSE
    return FALSE;
}
