#include "MyDialog.h"

static void test_dialog(GtkWidget *widget,GtkWindow *win){
    MyDialog *dialog1;
    dialog1=my_dialog_new();
    gtk_widget_show_all((GtkWidget*)dialog1);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*overlay,*btntest;
    //Initalize main_window
    window=gtk_application_window_new(app);
    gtk_window_set_default_size((GtkWindow*)window,200,200);
    gtk_window_set_icon_name((GtkWindow*)window,"org.gtk.daleclack");
    //Overlay
    overlay=gtk_overlay_new();
    //Button
    btntest=gtk_button_new_with_label("Test");
    gtk_widget_set_halign(btntest,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(btntest,GTK_ALIGN_CENTER);
    g_signal_connect(btntest,"clicked",G_CALLBACK(test_dialog),NULL);
    gtk_overlay_add_overlay((GtkOverlay*)overlay,btntest);
    //Add overlay and show everything
    gtk_container_add((GtkContainer*)window,overlay);
    gtk_widget_show_all(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclak",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run((GApplication*)app,argc,argv);
}
