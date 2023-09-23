#pragma once

#include <gtk/gtk.h>

// File name and path limits
#define name_max_length 256
#define path_max_length 4096

#define MY_ITEM_TYPE (my_item_get_type())
G_DECLARE_FINAL_TYPE(MyItem, my_item, MY, ITEM, GObject)

const char *my_item_get_filename(MyItem *item);

const char *my_item_get_dispname(MyItem *item);

MyItem *my_item_new(const char *dispname, const char *filename);
