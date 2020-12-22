#include "gtkwin.h"
#include "test.h"
#include "winpe.xpm"
#include "360.xpm"

void Icon::get_image(const gchar **str,int width,int height){
    pixbuf=gdk_pixbuf_new_from_xpm_data(str);
    sized=gdk_pixbuf_scale_simple(pixbuf,width,height,GDK_INTERP_BILINEAR);
    img1=gtk_image_new_from_pixbuf(sized);
}

//Initalize GtkButton
void GtkBtn::init(const gchar *str,int width,int height){
    button=gtk_button_new_with_label(str);
    gtk_widget_set_size_request(button,width,height);
}

//Link "clicked" signal
void GtkBtn::signal_clicked(pfun func,gpointer data){
    g_signal_connect(button,"clicked",G_CALLBACK(func),data);
}

//put widget int layout
void Winlayout::put(GtkWidget *child,int x,int y){
    gtk_layout_put(GTK_LAYOUT(layout),child,x,y);
}

//Initalize Gtklayout
void Winlayout::init(){
    Icon background;
    background.get_image(winpe,400,300);
    put(background.img1,0,0);
    GtkBtn button1;
    button1.init("Test",100,50);
    button1.signal_clicked(print,NULL);
    put(button1.button,150,100);
}

void WinHeader::init(GtkWidget *window){
    MenuBar menubar;
    menubar.menu_init(window);
    gtk_header_bar_set_show_close_button(_header,TRUE);
    gtk_header_bar_set_decoration_layout(_header,"close,minimize,maximize:icon");
    pack_start(menubar.menubar);
}

void WinHeader::pack_start(GtkWidget *child){
    gtk_header_bar_pack_start(_header,child);
}

void MenuBar::menubar_append(Menuitem child){
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar),child.menuitem);
}

void MenuBar::menu_init(GtkWidget *window){
    Menuitem menuitem2;
    Menu menu;
    menuitem2.menuitem_init("File",NULL,NULL);
    menubar_append(menuitem2);
    menu.set_submenu(menuitem2);
    menuitem2.menuitem_init("Exit",quit,(gpointer)window);
    menu.menu_append(menuitem2);

    menuitem2.menuitem_init("config",NULL,NULL);
    menubar_append(menuitem2);
    menu.set_submenu(menuitem2);
    menuitem2.menuitem_init("Change config",config_activate,NULL);
    menu.menu_append(menuitem2);

    menuitem2.menuitem_init("Help",NULL,NULL);
    menubar_append(menuitem2);
    menu.set_submenu(menuitem2);
    menuitem2.menuitem_init("About",about_activate,NULL);
    menu.menu_append(menuitem2);
}

void Menu::menu_append(Menuitem child){
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),child.menuitem);
}

void Menu::set_submenu(Menuitem menuitem){
    menu=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem.menuitem),menu);
}

void Menuitem::menuitem_init(const gchar *str,pfun func,gpointer data){
    menuitem=gtk_menu_item_new_with_label(str);
    if(func!=NULL){
    g_signal_connect(menuitem,"activate",G_CALLBACK(func),data);
    }
}

//Add widget to window
void GtkWin::add(GtkWidget *widget){
    gtk_container_add(GTK_CONTAINER(window),widget);
}


void GtkWin::win_init(GtkApplication *app,int width,int height){
    Icon icon1;
    icon1.get_image(_60,50,50);
    //Create a window and set window proprites
    window=gtk_application_window_new(app);
    _window=GTK_WINDOW(window);
    gtk_window_set_default_size(_window,width,height);
    gtk_window_set_position(_window,GTK_WIN_POS_CENTER);
    gtk_window_set_icon(_window,icon1.pixbuf);
    //Set window titlebar
    WinHeader header1;
    header1.init(window);
    set_titlebar(header1.header);
    //Put a layout
    Winlayout layout1;
    layout1.init();
    add(layout1.layout);
}

void GtkWin::set_titlebar(GtkWidget *title){
    gtk_window_set_titlebar(_window,title);
}

//Show everything
void GtkWin::show_all(){
    gtk_widget_show_all(window);
}

void HBox::pack_start(GtkWidget *child,gboolean expand,gboolean full,gint padding){
    gtk_box_pack_start(GTK_BOX(hbox),child,expand,full,padding);
}
