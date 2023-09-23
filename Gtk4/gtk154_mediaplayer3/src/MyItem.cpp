#include "MyItem.h"
#include <cstring>

struct _MyItem
{
    GObject parent_instance;
    char disp_name[name_max_length];
    char file_name[path_max_length];
};

G_DEFINE_TYPE(MyItem, my_item, G_TYPE_OBJECT)

const char *my_item_get_filename(MyItem *item)
{
    // Get true file name
    return item->file_name;
}

const char *my_item_get_dispname(MyItem *item)
{
    // Get Base name
    return item->disp_name;
}

static void my_item_init(MyItem *self)
{
}

static void my_item_class_init(MyItemClass *klass)
{
}

MyItem *my_item_new(const char *dispname, const char *filename)
{
    // Create a new item
    MyItem *item = MY_ITEM(g_object_new(my_item_get_type(), NULL));
    strncpy(item->disp_name, dispname, name_max_length);
    strncpy(item->file_name, filename, path_max_length);
    return item;
}
