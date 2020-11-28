#include <gtk/gtk.h>
#include "winpe.xpm"
#include "img.xpm"

void hello(GtkWidget *widget,gpointer data){
    //Create a dialog window
    GtkWidget *dialog;
    dialog=gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog),"gtk (21)");
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);

    //create dialog image
    GdkPixbuf *img2;
    GdkPixbuf *size2;
    GtkWidget *image2;
    img2=gdk_pixbuf_new_from_xpm_data(img);
    size2=gdk_pixbuf_scale_simple(img2,40,40,GDK_INTERP_BILINEAR);
    image2=gtk_image_new_from_pixbuf(size2);

    //Get content area and put widgets
    GtkWidget *content_area;
    GtkWidget *hbox;
    GtkWidget *label;
    GtkWidget *label1;
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label1=gtk_label_new("   ");
    gtk_container_add(GTK_CONTAINER(content_area),label1);
    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
    label1=gtk_label_new("   ");
    gtk_box_pack_start(GTK_BOX(hbox),label1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox),image2,FALSE,FALSE,0);
    label=gtk_label_new("gtk (21) By daleclack");
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
    gtk_container_add(GTK_CONTAINER(content_area),hbox);

    //Run the dialog
    gtk_widget_show_all(content_area);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    g_object_unref(img2);
    g_object_unref(size2);
}

static void activate(GtkApplication *app,gpointer user_data){
    //Create a window and set size,positon,title and icon
    GtkWidget *window;
    GdkPixbuf *icon1=gdk_pixbuf_new_from_xpm_data(img);
    window=gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window),"gtk (21)");
    gtk_window_set_default_size(GTK_WINDOW(window),400,300);
    gtk_window_set_icon(GTK_WINDOW(window),icon1);

    //Create the background of the window
    GdkPixbuf *image;
    GdkPixbuf *sized;
    GtkWidget *image1;
    image=gdk_pixbuf_new_from_xpm_data(winpe);
    sized=gdk_pixbuf_scale_simple(image,400,300,GDK_INTERP_BILINEAR);
    image1=gtk_image_new_from_pixbuf(sized);

    //Put the background to window
    GtkWidget *layout;
    layout=gtk_layout_new(NULL,NULL);
    gtk_layout_put(GTK_LAYOUT(layout),image1,0,0);

    //Create a button and put it into the window
    GtkWidget *button;
    button=gtk_button_new_with_label("OK");
    gtk_widget_set_size_request(button,100,50);
    gtk_layout_put(GTK_LAYOUT(layout),button,150,200);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),NULL);

    //Show all widgets
    gtk_container_add(GTK_CONTAINER(window),layout);
    gtk_widget_show_all(window);
    g_object_unref(image);
    g_object_unref(sized);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.daleclack.gtk21",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
