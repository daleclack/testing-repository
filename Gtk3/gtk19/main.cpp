#include <gtk/gtk.h>

static void activate(GtkApplication *app,gpointer user_data)
{
//Create a window
    GtkWidget *window=gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"gtk (19)");
    gtk_window_set_default_size(GTK_WINDOW(window),400,300);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    //Create a gtk notebook
    GtkWidget *notebook=gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook),GTK_POS_TOP);
    //GtkNotebook page 1
    GtkWidget *hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget *label1=gtk_label_new("Label Page 1");
    GtkWidget *label=gtk_label_new("Page 1");
    gtk_box_pack_start(GTK_BOX(hbox),label1,TRUE,TRUE,0);
    GtkWidget *button1=gtk_button_new_with_label("Button 1");
    gtk_box_pack_start(GTK_BOX(hbox),button1,TRUE,TRUE,0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),hbox,label);
    //GtkNotebook page 2
    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget *label2=gtk_label_new("Label Page 2");
    label=gtk_label_new("Page 2");
    gtk_box_pack_start(GTK_BOX(hbox),label2,TRUE,TRUE,0);
    GtkWidget *button2=gtk_button_new_with_label("Button 2");
    gtk_box_pack_start(GTK_BOX(hbox),button2,TRUE,TRUE,0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),hbox,label);//append a new page
    //GtkNotebook page 3
    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    GtkWidget *label3=gtk_label_new("Label Page 3");
    label=gtk_label_new("Page 3");
    gtk_box_pack_start(GTK_BOX(hbox),label3,TRUE,TRUE,0);
    GtkWidget *button3=gtk_button_new_with_label("Button 3");
    gtk_box_pack_start(GTK_BOX(hbox),button3,TRUE,TRUE,0);
    gtk_notebook_insert_page(GTK_NOTEBOOK(notebook),hbox,label,2);//insert a new page
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook),0);//Set default page of gtknotebook
    gtk_container_add(GTK_CONTAINER(window),notebook);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[])
{
//Common way to create a gtk+ app
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.daleclack.gtk19",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
