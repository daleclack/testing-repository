#include<gtk/gtk.h>
#include"img.xpm"
#include"xeapi.h"

void MsgBox(GtkWidget *widget,gpointer data){
    GtkWidget *dialog;
    GtkWidget *label;
    GtkWidget *content_area;
    GdkPixbuf *image;
    GdkPixbuf *sized_img;
    GtkWidget *image1;
    GtkWidget *hbox;
    GtkWidget *label1;
    time_t t;
    struct tm *local;
    t=time(NULL);//Get local time
    local=localtime(&t);
    char str[57];//Api version
    sprintf(str,"Api:%d",xeapi1(local));
    dialog=gtk_dialog_new();//Create a new dialog and set profiles
    gtk_window_set_title(GTK_WINDOW(dialog),"Xeinit");
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(dialog),200,90);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);//Create a new button
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label=gtk_label_new(str);//label to show string in str
    image=gdk_pixbuf_new_from_xpm_data(img);//Get a image from xpm data and change size of the image
    sized_img=gdk_pixbuf_scale_simple(image,30,30,GDK_INTERP_BILINEAR);
    image1=gtk_image_new_from_pixbuf(sized_img);//Convert to image widget for use
    label1=gtk_label_new("     ");//Spacing
    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);//Gtk box to change layouts
    gtk_container_add(GTK_CONTAINER(content_area),hbox);
    gtk_box_pack_start(GTK_BOX(hbox),label1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox),image1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
    gtk_widget_show_all(hbox);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int main(int argc,char *argv[]){
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *fixed;
    GdkPixbuf *image;
    GdkPixbuf *sized_img;
    GtkWidget *image1;
    gtk_init(&argc,&argv);
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);//Create a new window
    gtk_window_set_title(GTK_WINDOW(window),"gtk (16)");
    gtk_window_set_default_size(GTK_WINDOW(window),300,100);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed=gtk_fixed_new();//Gtk_fixed:Put widgets
    gtk_container_add(GTK_CONTAINER(window),fixed);
    image=gdk_pixbuf_new_from_xpm_data(img);//Get a image from xpm data and change image size
    sized_img=gdk_pixbuf_scale_simple(image,30,30,GDK_INTERP_BILINEAR);
    image1=gtk_image_new_from_pixbuf(sized_img);
    button=gtk_button_new_with_label("Xe-Api");//Change button size and add image
    gtk_widget_set_size_request(button,120,40);
    gtk_button_set_image(GTK_BUTTON(button),image1);
    gtk_fixed_put(GTK_FIXED(fixed),button,90,25);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(MsgBox),NULL);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
