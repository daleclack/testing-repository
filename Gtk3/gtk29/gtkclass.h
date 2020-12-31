#include <gtk/gtk.h>

class GtkWin{
    GtkWindow *_window;
    public:
    GtkWidget *window;
    void init(GtkApplication *app,int width,int height);
    void set_titlebar(GtkWidget *titlebar);
    void present();
};

class WinHeader{
    GtkHeaderBar *_header;
    public:
    GtkWidget *header;
    void header_init(const gchar *title);
};
