#include "MineSweeper.h"
#include "MineCell.h"

struct _MineSweeper
{
    GtkApplicationWindow parent_instance;
};

G_DEFINE_TYPE(MineSweeper, mine_sweeper, GTK_TYPE_APPLICATION_WINDOW)

static void mine_sweeper_init(MineSweeper *self)
{

}

static void mine_sweeper_class_init(MineSweeperClass *klass)
{

}

MineSweeper *mine_sweeper_new()
{
    return MINE_SWEEPER(g_object_new(mine_sweeper_get_type(), NULL));
}
