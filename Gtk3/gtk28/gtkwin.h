#include <gtk/gtk.h>

typedef void(*pfun)(GtkWidget *,gpointer);//define a pointer to function

//GtkButton class
class GtkBtn{
    public:
    GtkWidget *button;
    void init(const gchar *str,int width,int height);
    void signal_clicked(pfun func,gpointer data);
};

//GtkLayout class
class Winlayout{
    void put(GtkWidget *child,int x,int y);
    public:
    GtkWidget *layout=gtk_layout_new(NULL,NULL);
    void init();
};

//GtkWindow class
class GtkWin{
    GtkWidget *window;
    GtkWindow *_window;
    void add(GtkWidget *widget);
    public:
    void win_init(GtkApplication *app,int width,int height);
    void show_all();
};

