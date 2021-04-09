#include <gtk/gtk.h>

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkBuilder *builder=gtk_builder_new_from_file("res/window.ui");
    GtkWidget *window,*stack;
    window=(GtkWidget*)gtk_builder_get_object(builder,"window");
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    stack=(GtkWidget*)gtk_builder_get_object(builder,"stack1");
    gtk_stack_set_visible_child_name(GTK_STACK(stack),"Child1");
    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_widget_show_all(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}