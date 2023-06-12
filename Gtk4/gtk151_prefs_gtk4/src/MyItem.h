#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MyItem, my_item, MY, ITEM, GObject)

// File name and path limits
const int name_max_length = 256;
const int path_max_length = 4096;

// Create a new item
MyItem *my_item_new(const char *disp_name, const char *path,
                    gboolean internal1);

// Get display name
const char *my_item_get_display_name(MyItem *item);

// Get Path
const char *my_item_get_path(MyItem *item);

// Get whether the image is internal
gboolean my_item_get_internal(MyItem *item);
