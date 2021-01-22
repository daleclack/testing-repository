#include <gtk/gtk.h>

void print_letters(GtkWidget *widget,gpointer data){
    const gchar *str=gtk_button_get_label(GTK_BUTTON(widget));
    g_print("%s\n",str);
}

void print(GtkWidget *widget,gchar *data){
    g_print("%s\n",data);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkBuilder *builder=gtk_builder_new_from_file("window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    gtk_application_add_window(app,GTK_WINDOW(window));
    //charactor buttons
    GObject *btn[27];
    for(int i=1;i<=26;i++){
        char name[10];
        sprintf(name,"btn%d",i);
        btn[i]=gtk_builder_get_object(builder,name);
        g_signal_connect(btn[i],"clicked",G_CALLBACK(print_letters),NULL);
    }
    GObject *btn_ctrl=gtk_builder_get_object(builder,"btnctrl");
    g_signal_connect(btn_ctrl,"clicked",G_CALLBACK(print_letters),NULL);
    GObject *btn_alt=gtk_builder_get_object(builder,"btnalt");
    g_signal_connect(btn_alt,"clicked",G_CALLBACK(print_letters),NULL);
    GObject *btn_space=gtk_builder_get_object(builder,"btnspace");
    g_signal_connect(btn_space,"clicked",G_CALLBACK(print),(gpointer)" ");
    GObject *btn_enter=gtk_builder_get_object(builder,"btnenter");
    g_signal_connect(btn_enter,"clicked",G_CALLBACK(print),(gpointer)"");
    GObject *btn_quit=gtk_builder_get_object(builder,"btnquit");
    g_signal_connect_swapped(btn_quit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk36",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}