#include "ScoresItem.h"

struct _ScoresItem
{
    GObject parent_instance;
    char name[NAME_MAX];
    int time;
};

G_DEFINE_TYPE(ScoresItem, scores_item, G_TYPE_OBJECT)

static void scores_item_init(ScoresItem *self)
{
}

static void scores_item_class_init(ScoresItemClass *klass)
{
}

ScoresItem *scores_item_new(const char *win_name, int win_time)
{
    ScoresItem *item = Scores_Item(g_object_new(scores_item_get_type(), NULL));
    strncpy(item->name, win_name, NAME_MAX);
    item->time = win_time;
    return item;
}


const char *scores_item_get_name(ScoresItem *item)
{
    return item->name;
}

void scores_item_set_name(ScoresItem *item, const char *win_name)
{
    strncpy(item->name, win_name, NAME_MAX);
}

int scores_item_get_time(ScoresItem *item)
{
    return item->time;
}

void scores_item_set_time(ScoresItem *item, int win_time)
{
    item->time = win_time;
}
