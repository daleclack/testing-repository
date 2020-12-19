#include <gtk/gtk.h>

class Winlayout{
    public:
    GtkWidget *layout=gtk_layout_new(NULL,NULL);
    void put(GtkWidget *child,int x,int y);
};

class GtkWin{
    GtkWindow *_window;
    public:
    GtkWidget *main_window;
    void win_init(int width,int height);
    void set_titlebar(GtkWidget *widget);
    void add_widget(GtkWidget *widget);
    void show_all();
};

class Winheader{
    GtkHeaderBar *_header;
    public:
    GtkWidget *header=gtk_header_bar_new();
    void header_init();
    void pack_start(GtkWidget *child);
    void pack_end(GtkWidget *child);
};

