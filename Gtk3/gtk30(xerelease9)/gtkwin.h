#include <gtk/gtk.h>

typedef void(*pfun)(GtkWidget *,gpointer);//define a pointer to function

//Convert xpm data to a GtkImage
class Icon{
    GdkPixbuf *sized;
    public:
    GdkPixbuf *pixbuf;
    GtkWidget *img1;
    void get_image(const gchar **str,int width,int height);
};

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

//GtkHeaderbar class
class WinHeader{
    public:
    GtkWidget *header=gtk_header_bar_new();
    GtkHeaderBar *_header=GTK_HEADER_BAR(header);
    void init(GtkWidget *window);
    void pack_start(GtkWidget *child);
};

//GtkMenuitem class
class Menuitem{
    public:
    GtkWidget *menuitem;
    void menuitem_init(const gchar *str,pfun func,gpointer data);
};

//GtkMenuBar class
class MenuBar{
    public:
    GtkWidget *menubar=gtk_menu_bar_new();
    void menubar_append(Menuitem child);
    void menu_init(GtkWidget *window);
};

//GtkMenu class
class Menu{
    public:
    GtkWidget *menu;
    void menu_append(Menuitem child);
    void set_submenu(Menuitem menuitem);
};

//GtkWindow class
class GtkWin{
    GtkWidget *window;
    GtkWindow *_window;
    void add(GtkWidget *widget);
    public:
    void set_titlebar(GtkWidget *title);
    void win_init(GtkApplication *app,int width,int height);
    void show_all();
};

//GtkHBox class (Not the deprecated GtkHbox)
class HBox{
    public:
    GtkWidget *hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    void pack_start(GtkWidget *child,gboolean expand,gboolean full,gint padding);
};

//GtkComboBox class
class Combobox{
    public:
    GtkWidget *combo;
    void append_item(const gchar *str);
    void init(int width,int height);
};
