#include <gtk/gtk.h>

void entry_activate(GtkWidget *widget,GtkDialog *dialog){
    gtk_dialog_response(dialog,GTK_RESPONSE_OK);
}

double InputBox(void){
    //Get dialog and initalize
    GtkBuilder *builder=gtk_builder_new_from_file("res/InputBox.ui");
    GObject *dialog=gtk_builder_get_object(builder,"inputbox");
    GObject *entry=gtk_builder_get_object(builder,"entrymax");
    g_signal_connect(entry,"activate",G_CALLBACK(entry_activate),dialog);
    int res=gtk_dialog_run(GTK_DIALOG(dialog));
    //if clicked "OK" button,get text and change the text to a number
    double maxinum;
    if(res==GTK_RESPONSE_OK){
        const gchar *text;
        text=gtk_entry_get_text(GTK_ENTRY(entry));
        maxinum=atof(text);
        //g_print("OK\n");
    }
    gtk_widget_destroy(GTK_WIDGET(dialog));
    return maxinum;
}

void scale_change(GtkWidget *widget,GtkBuilder *builder){
    //Change the maxinum of the adjustment
    double max=InputBox();
    GObject *adjust=gtk_builder_get_object(builder,"adjustment1");
    gtk_adjustment_set_upper(GTK_ADJUSTMENT(adjust),max);
    //g_print("%d\n",max);
}

static void gtkmain(GtkApplication *app,gpointer *user_data){
    //Main window
    GtkBuilder *builder=gtk_builder_new_from_file("res/window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    gtk_application_add_window(app,GTK_WINDOW(window));
    //"Change" button
    GObject *btn_change=gtk_builder_get_object(builder,"btnchange");
    g_signal_connect(btn_change,"clicked",G_CALLBACK(scale_change),builder);
    //"Exit" button
    GObject *btn_exit=gtk_builder_get_object(builder,"btnexit");
    g_signal_connect_swapped(btn_exit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    //Start a gtk application
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk38",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
