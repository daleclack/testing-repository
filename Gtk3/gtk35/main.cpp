#include <gtk/gtk.h>

void file_dialog(GtkWidget *widget,gpointer data){
    GtkFileChooserAction action=GTK_FILE_CHOOSER_ACTION_OPEN;
    GtkWidget *dialog=gtk_file_chooser_dialog_new("Open File",GTK_WINDOW(data),action,
    "Cencel",GTK_RESPONSE_CANCEL,"OK",GTK_RESPONSE_OK,NULL);
    gint res;
    res=gtk_dialog_run(GTK_DIALOG(dialog));
    if(res==GTK_RESPONSE_OK){
        char *filename;
        filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        g_print("%s\n",filename);
    }
    gtk_widget_destroy(dialog);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Main window
    GtkBuilder *builder=gtk_builder_new_from_file("window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    gtk_application_add_window(app,GTK_WINDOW(window));
    //dialog button
    GObject *btn_dialog=gtk_builder_get_object(builder,"btnchoose");
    g_signal_connect(btn_dialog,"clicked",G_CALLBACK(file_dialog),window);
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk35",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}