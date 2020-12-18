#include <gtk/gtk.h>
#include "360.xpm"
#include "img.xpm"
#include "winpe.xpm"

struct GtkWin{
    //This struct is a gtk window and some useful functions
    GtkWidget *window;
    //Window Settings
    void win_init(int width,int height){
        gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
        gtk_window_set_default_size(GTK_WINDOW(window),width,height);
    }
    //Window Settings
    void add(GtkWidget *widget){
        gtk_container_add(GTK_CONTAINER(window),widget);
    }
    //Show everything
    void show_all(){
        gtk_widget_show_all(window);
    }
    //Set custom title bar
    void set_titlebar(GtkWidget *widget){
        gtk_window_set_titlebar(GTK_WINDOW(window),widget);
    }
     //Set window icon
    void set_icon(GdkPixbuf *icon){
        gtk_window_set_icon(GTK_WINDOW(window),icon);
    }
};

struct WinHeader{
    //This struct is a GtkHeader widget
    GtkWidget *header=gtk_header_bar_new();
    //header initialize
    void init(const char *title){
        //gtk_header_bar_set_title(GTK_HEADER_BAR(header),title);
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header),TRUE);
        gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header),"close,minimize,maximize:menu");
    }
    //Put widgets from the left(default)
    void pack_start(GtkWidget *child){
        gtk_header_bar_pack_start(GTK_HEADER_BAR(header),child);
    }
    //Put widgets from the right(default)
    void pack_end(GtkWidget *child){
        gtk_header_bar_pack_end(GTK_HEADER_BAR(header),child);
    }
};

struct VBox{
    //This struct is a GtkVBox widget and a function
    GtkWidget *box=gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    //Put widget to the vbox
    void pack_start(GtkWidget *child,gboolean expand,gboolean full,guint padding){
        gtk_box_pack_start(GTK_BOX(box),child,expand,full,padding);
    }
};

struct HBox{
    //This struct is GtkHBox widget and function
    GtkWidget *box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
    //Put widgets to the box
    void pack_start(GtkWidget *child,gboolean expand,gboolean full,guint padding){
        gtk_box_pack_start(GTK_BOX(box),child,expand,full,padding);
    }
};

struct MenuBar{
    //This struct is GtkMenuBar widget
    GtkWidget *menubar1=gtk_menu_bar_new();
    //Append item to the menubar
    void append(GtkWidget *child){
        gtk_menu_shell_append(GTK_MENU_SHELL(menubar1),child);
    }
};

struct Menu{
    //This struct is GtkMenu and some functions
    GtkWidget *menu1;
    //Set the menu as a submenu of a menuitem
    void add_submenu(GtkWidget *menuitem1){
        menu1=gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem1),menu1);
    }
    //Append item to the menu
    void append(GtkWidget *child){
        gtk_menu_shell_append(GTK_MENU_SHELL(menu1),child);
    }
};

struct MenuButton{};

struct Xpm_image{
    //Get xpm data from char and create a image from the xpm
    GdkPixbuf *pixbuf;
    GdkPixbuf *sized;
    GtkWidget *image;
    void init(const char **src_xpm_data,int dest_width,int dest_height){
        pixbuf=gdk_pixbuf_new_from_xpm_data(src_xpm_data);
        sized=gdk_pixbuf_scale_simple(pixbuf,dest_width,dest_height,GDK_INTERP_BILINEAR);
        image=gtk_image_new_from_pixbuf(sized);
    }
};

struct MsgDialog{
    //A Message Dialog
    GtkWidget *dialog=gtk_dialog_new();
    GtkDialog *dialog1=GTK_DIALOG(dialog);
    GtkContainer *content_area=(GtkContainer*)gtk_dialog_get_content_area(dialog1);
    HBox hbox;
    Xpm_image icon1;
    //add the message string and a icon to message box
    void add_msg(const gchar *msg){
        //g_print(msg);
        GtkWidget *label=gtk_label_new(" ");
        gtk_container_add(content_area,label);
        icon1.init(_60,40,40);
        hbox.pack_start(icon1.image,FALSE,FALSE,10);
        label=gtk_label_new(msg);
        hbox.pack_start(label,FALSE,FALSE,0);
        gtk_container_add(content_area,hbox.box);
        gtk_widget_show_all(dialog);
    }
    //Initalize the Message Box
    void init(const gchar *msg,const gchar *title,int width,int height){
        GtkWindow *dialog_win=GTK_WINDOW(dialog);
        gtk_window_set_title(dialog_win,title);
        gtk_window_set_default_size(dialog_win,width,height);
        gtk_window_set_position(dialog_win,GTK_WIN_POS_CENTER);
        add_msg(msg);
        gtk_dialog_add_button(dialog1,"OK",GTK_RESPONSE_OK);
    }
    //Run the Message Box
    void run(){
        gtk_dialog_run(dialog1);
        gtk_widget_destroy(dialog);
    }
};

struct WinLayout{
    //GtkLayout widget
    GtkWidget *layout=gtk_layout_new(NULL,NULL);
    //Put widget to layout
    void put(GtkWidget *child,int x,int y){
        gtk_layout_put(GTK_LAYOUT(layout),child,x,y);
    }
};

//Callback function of "About" menuitem,create a dialog and run it
void MsgBox(GtkWidget *widget,gpointer data){
    MsgDialog msg1;
    msg1.init("Gtk26 by daleclack\nProgrammed on code::blocks\nGui:gtk+3.24","gtk (26)",300,150);
    msg1.run();
}

//Initalize menu
void menu_config(MenuBar menubar,Menu menu,GtkWin window1){
    GtkWidget *menuitem;
    //"File" menu
    menuitem=gtk_menu_item_new_with_label("File");
    menubar.append(menuitem);
    menu.add_submenu(menuitem);
    menuitem=gtk_menu_item_new_with_label("Exit");
    menu.append(menuitem);
    g_signal_connect_swapped(menuitem,"activate",G_CALLBACK(gtk_widget_destroy),window1.window);

    //"Game" menu
    menuitem=gtk_menu_item_new_with_label("Game");
    menubar.append(menuitem);
    menu.add_submenu(menuitem);
    menuitem=gtk_menu_item_new_with_label("Reset");
    menu.append(menuitem);

    //"Help" menu
    menuitem=gtk_menu_item_new_with_label("Help");
    menubar.append(menuitem);
    menu.add_submenu(menuitem);
    menuitem=gtk_menu_item_new_with_label("About");
    menu.append(menuitem);
    g_signal_connect(menuitem,"activate",G_CALLBACK(MsgBox),NULL);
}

static void activate(GtkApplication *app,gpointer user_data){
    //Create a app window and initalize
    GtkWin window1;
    Xpm_image win_icon;
    window1.window=gtk_application_window_new(app);
    window1.win_init(400,300);
    win_icon.init(img,50,50);
    window1.set_icon(win_icon.pixbuf);

    //Create a layout
    WinLayout layout1;
    Xpm_image background;
    background.init(winpe,400,300);
    layout1.put(background.image,0,0);

    //Create a menu
    MenuBar menubar;
    Menu menu;
    menu_config(menubar,menu,window1);

    //Initalize GtkHeader and make it as title bar
    WinHeader header1;
    header1.init("gtk (26)");
    header1.pack_start(menubar.menubar1);
    window1.set_titlebar(header1.header);
    GtkWidget *menubtn=gtk_menu_button_new();
    header1.pack_end(menubtn);

    //Add layout to the window and show everything
    window1.add(layout1.layout);
    window1.show_all();
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("org.gtk.example",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
