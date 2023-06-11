#include "MyItem.h"

struct _MyItem
{
    GObject parent_instance;
    const char *col_name, *col_path;
    gboolean internal;
};

G_DEFINE_TYPE(MyItem, my_item, G_TYPE_OBJECT)

// Get display name
const char *my_item_get_display_name(MyItem *item)
{
    return item->col_name;
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
    item->col_name = disp_name;
    item->col_path = path;
    item->internal = internal1;
    return item;
}
