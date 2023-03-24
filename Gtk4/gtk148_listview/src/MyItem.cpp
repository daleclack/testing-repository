#include "MyItem.h"

struct _MyItem{
    GObject parent_instance;
    GString *string;
};

G_DEFINE_TYPE(MyItem, my_item, G_TYPE_OBJECT)

static void my_item_dispose(GObject *object){
    // Free the memory
    g_string_free(MY_ITEM(object)->string, TRUE);
    G_OBJECT_CLASS(my_item_parent_class)->dispose(object);
}

static void my_item_init(MyItem *self){
}

static void my_item_class_init(MyItemClass *klass){
    G_OBJECT_CLASS(klass)->dispose = my_item_dispose;
}

GString *my_item_get_string(MyItem *self){
    return self->string;
}

MyItem *my_item_new(const char *str){
    // Create a new MyItem and initalize
    MyItem *item = MY_ITEM(g_object_new(my_item_get_type(), NULL));
    item->string = g_string_new(str);
    return item;
}
