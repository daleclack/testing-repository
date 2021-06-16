#include <gtk/gtk.h>

static GtkWidget *infobar;

void textbuffer_clear(GtkWidget *widget,GtkTextBuffer *buffer){
    gtk_text_buffer_set_text(buffer,"",-1);
    gtk_widget_show(infobar);
}

void infobar_response(GtkWidget *widget,gpointer data){
    gtk_widget_hide(widget);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Initalize window
    GtkWidget *window,*vbox;
    window=gtk_application_window_new(app);
    gtk_window_set_icon_name((GtkWindow*)window,"org.gtk.daleclack");
    gtk_window_set_default_size((GtkWindow*)window,800,450);
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,5);

    //Initalize infobar
    infobar=gtk_info_bar_new_with_buttons("OK",GTK_RESPONSE_OK,NULL);
    GtkWidget *content_area=gtk_info_bar_get_content_area((GtkInfoBar*)infobar);
    GtkWidget *label=gtk_label_new("Cleared the text");
    g_signal_connect(infobar,"response",G_CALLBACK(infobar_response),NULL);
    gtk_container_add((GtkContainer*)content_area,label);
    gtk_box_pack_start((GtkBox*)vbox,infobar,TRUE,FALSE,0);

    //Ininalize TextView
    GtkWidget *textview;
    GtkTextBuffer *textbuffer;
    textview=gtk_text_view_new();
    textbuffer=gtk_text_view_get_buffer((GtkTextView*)textview);
    gtk_widget_set_size_request(textview,800,440);
    gtk_box_pack_start((GtkBox*)vbox,textview,TRUE,TRUE,0);

    //Add Buttons
    GtkWidget *btn_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    GtkWidget *btnclear,*btnexit;
    btnclear=gtk_button_new_with_label("Clear");
    g_signal_connect(btnclear,"clicked",G_CALLBACK(textbuffer_clear),textbuffer);
    btnexit=gtk_button_new_with_label("Exit");
    g_signal_connect_swapped(btnexit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_box_pack_end((GtkBox*)btn_box,btnexit,FALSE,FALSE,0);
    gtk_box_pack_end((GtkBox*)btn_box,btnclear,FALSE,FALSE,0);
    gtk_box_pack_end((GtkBox*)vbox,btn_box,TRUE,FALSE,0);

    //Add widgets and show everything
    gtk_container_add((GtkContainer*)window,vbox);
    gtk_widget_show_all(window);
    gtk_widget_hide(infobar);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run((GApplication*)app,argc,argv);
}