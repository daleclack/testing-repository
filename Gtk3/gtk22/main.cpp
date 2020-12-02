#include <gtk/gtk.h>
#include "winpe.xpm"
#include "img.xpm"

void MsgBox(GtkWidget *widget,gpointer data)
{
    GtkWidget *dialog;
    dialog=gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog),"gtk (22)");
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);

    GdkPixbuf *img1;
    GdkPixbuf *sized;
    GtkWidget *img2;
    img1=gdk_pixbuf_new_from_xpm_data(img);
    sized=gdk_pixbuf_scale_simple(img1,50,50,GDK_INTERP_BILINEAR);
    img2=gtk_image_new_from_pixbuf(sized);

    GtkWidget *content_area;
    GtkWidget *hbox;
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget *label1=gtk_label_new("   ");
    gtk_container_add(GTK_CONTAINER(content_area),label1);
    label1=gtk_label_new("   ");
    gtk_box_pack_start(GTK_BOX(hbox),label1,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(hbox),img2,FALSE,FALSE,5);
    label1=gtk_label_new("Xeinit By daleclack\n2020 Xe Corporation");
    gtk_box_pack_start(GTK_BOX(hbox),label1,FALSE,FALSE,5);

    gtk_container_add(GTK_CONTAINER(content_area),hbox);
    gtk_widget_show_all(content_area);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void activate(GtkApplication *app,gpointer user_data)
{
    GtkWidget *window;
    window=gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window),"gtk (22)");
    gtk_window_set_default_size(GTK_WINDOW(window),400,300);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    GtkWidget *vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    GtkWidget *menu,*menubar,*menuitem;
    menubar=gtk_menu_bar_new();

    menuitem=gtk_menu_item_new_with_label("File");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar),menuitem);
    menu=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem),menu);
    menuitem=gtk_menu_item_new_with_label("Exit");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
    g_signal_connect_swapped(G_OBJECT(menuitem),"activate",G_CALLBACK(gtk_widget_destroy),window);

    menuitem=gtk_menu_item_new_with_label("Xe-Ver");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar),menuitem);
    menu=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem),menu);
    menuitem=gtk_menu_item_new_with_label("xe 5.2");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
    menuitem=gtk_menu_item_new_with_label("xe 6.x");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);

    menuitem=gtk_menu_item_new_with_label("Help");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar),menuitem);
    menu=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem),menu);
    menuitem=gtk_menu_item_new_with_label("About");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu),menuitem);
    g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(MsgBox),NULL);

    gtk_box_pack_start(GTK_BOX(vbox),menubar,FALSE,FALSE,0);
    GtkWidget *layout;
    layout=gtk_layout_new(NULL,NULL);

    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(winpe);
    GdkPixbuf *img1=gdk_pixbuf_scale_simple(pixbuf,400,390,GDK_INTERP_BILINEAR);
    GtkWidget *img2=gtk_image_new_from_pixbuf(img1);
    gtk_layout_put(GTK_LAYOUT(layout),img2,0,0);
    gtk_box_pack_start(GTK_BOX(vbox),layout,TRUE,TRUE,0);

    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);
    g_object_unref(pixbuf);
    g_object_unref(img1);
}

int main(int argc,char *argv[])
{
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.daleclack.gtk22",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
