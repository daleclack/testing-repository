#include <gtk/gtk.h>
#include "gtkwin.h"
#include "config-test.h"
#include "img.xpm"
#include "winpe.xpm"

void gtkwin(GtkApplication *app,gpointer user_data)
{
//Main window
    GtkWidget *window;
    window=gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"gtk (23)");
    gtk_window_set_default_size(GTK_WINDOW(window),400,300);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    gtk_win_add_menu(window,NULL);

    gtk_widget_show_all(window);
}

void gtk_win_add_menu(GtkWidget *widget,gpointer data)
{
    //Add menu to the window
    GtkWidget *vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    GtkWidget *layout=gtk_layout_new(NULL,NULL);
    GtkWidget *menubar,*menu,*menuitem;
    menubar=gtk_menu_bar_new();

    //"File" menu
    menuitem=gtk_menu_item_new_with_label("File");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar),menuitem);
    menu=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem),menu);
    menuitem=gtk_menu_item_new_with_label("Exit");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
    g_signal_connect_swapped(menuitem,"activate",G_CALLBACK(gtk_widget_destroy),widget);

    //"Config" menu
    menuitem=gtk_menu_item_new_with_label("config");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar),menuitem);
    menu=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem),menu);
    menuitem=gtk_menu_item_new_with_label("Change config");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
    g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(config1),NULL);

    //"Help" menu
    menuitem=gtk_menu_item_new_with_label("Help");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar),menuitem);
    menu=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem),menu);
    menuitem=gtk_menu_item_new_with_label("About");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
    g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(about),NULL);

    gtk_layout_add_widgets(layout,NULL);

    gtk_box_pack_start(GTK_BOX(vbox),menubar,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),layout,FALSE,TRUE,0);
    gtk_container_add(GTK_CONTAINER(widget),vbox);
}

void gtk_layout_add_widgets(GtkWidget *widget,gpointer data)
{
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(winpe);
    GdkPixbuf *sized_img=gdk_pixbuf_scale_simple(pixbuf,400,390,GDK_INTERP_BILINEAR);
    GtkWidget *image1=gtk_image_new_from_pixbuf(sized_img);
    gtk_layout_put(GTK_LAYOUT(widget),image1,0,0);

    GtkWidget *button=gtk_button_new_with_label("Show Config");
    gtk_widget_set_size_request(button,100,50);
    gtk_layout_put(GTK_LAYOUT(widget),button,150,160);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(button_click),NULL);

    g_object_unref(pixbuf);
    g_object_unref(sized_img);
}

void button_click(GtkWidget *widget,gpointer data)
{
    char str[57];
    test(str);
    printf("%s",str);
}

void MsgBox(GtkWidget *widget,gpointer data,const gchar *str)
{
    //Create a dialog menu
    GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *content_area;
    gtk_window_set_title(GTK_WINDOW(dialog),"About");
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);

    //Create a image from xpm
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(img);
    GdkPixbuf *sized_img=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    GtkWidget *image=gtk_image_new_from_pixbuf(sized_img);

    //Put images to the dialog,the empty label as spacings
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget *label=gtk_label_new("   ");
    gtk_container_add(GTK_CONTAINER(content_area),label);
    label=gtk_label_new("   ");
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,5);
    GtkWidget *label1;
    label1=gtk_label_new(str);
    gtk_box_pack_start(GTK_BOX(hbox),label1,FALSE,FALSE,5);
    gtk_container_add(GTK_CONTAINER(content_area),hbox);

    gtk_widget_show_all(content_area);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    g_object_unref(pixbuf);
    g_object_unref(sized_img);
}

void InputBox(GtkWidget *widget,gpointer data)
{
    GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *content_area;
    GtkWidget *entry;
    const char * str;

    //Create dialog window
    gtk_window_set_title(GTK_WINDOW(dialog),"Input config");
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);

    //Create an entry and add it to the dialog window
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    entry=gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry),"hello");
    gtk_container_add(GTK_CONTAINER(content_area),entry);
    g_signal_connect(G_OBJECT(entry),"activate",G_CALLBACK(entry_activate),(gpointer)dialog);

    //Show everything
    gtk_widget_show_all(content_area);
    gtk_dialog_run(GTK_DIALOG(dialog));

    //Handle text in entry
    str=gtk_entry_get_text(GTK_ENTRY(entry));
    g_print(str);
    config(str);
    gtk_widget_destroy(dialog);
}

void config1(GtkWidget *widget,gpointer data)
{
  InputBox(widget,data);
}

void entry_activate(GtkWidget *widget,gpointer data)
{
    gtk_dialog_response(GTK_DIALOG(data),GTK_RESPONSE_OK);
}

void about(GtkWidget *widget,gpointer data)
{
    const gchar *msg="gtk23 by daleclack \n 2020 Xe Corporation";
    MsgBox(widget,data,msg);
}

