#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MyItem, my_item, MY, ITEM, GObject)

MyItem *my_item_new(const char *str);

GString *my_item_get_string(MyItem *self);
