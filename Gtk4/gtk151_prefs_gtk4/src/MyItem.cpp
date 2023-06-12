#include "MyItem.h"

// File name and path limits
#define name_max_length 256
#define path_max_length 4096

struct _MyItem
{
    GObject parent_instance;
    char col_name[name_max_length], col_path[path_max_length];
    gboolean internal;
};

G_DEFINE_TYPE(MyItem, my_item, G_TYPE_OBJECT)

// Get display name
const char *my_item_get_display_name(MyItem *item)
{
    return item->col_name;
}

// Get Path
const char *my_item_get_path(MyItem *item)
{
    return item->col_path;
}

// Get whether the image is internal
gboolean my_item_get_internal(MyItem *item)
{
    return item->internal;
}

static void my_item_init(MyItem *self)
{
}

static void my_item_class_init(MyItemClass *klass)
{
}

MyItem *my_item_new(const char *disp_name, const char *path,
                    gboolean internal1)
{
    // Create a object
    MyItem *item = MY_ITEM(g_object_new(my_item_get_type(), NULL));
    strncpy(item->col_name, disp_name, name_max_length);
    strncpy(item->col_path, path, path_max_length);
    item->internal = internal1;
    return item;
}
