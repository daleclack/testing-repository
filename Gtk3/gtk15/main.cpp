#include<gtk/gtk.h>

void add(GtkWidget *widget,gpointer data){//This function can change progress bar value
    gdouble new_val;
    new_val=gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(data));
    if(new_val>=1.0) new_val=0.0;
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data),new_val+0.05);
}

void change(GtkWidget *widget,gpointer data){
    //This function is for change progress bar orinentation:right ro left or left to right
    switch(gtk_progress_bar_get_inverted(GTK_PROGRESS_BAR(data))){
        case TRUE:
            gtk_progress_bar_set_inverted(GTK_PROGRESS_BAR(data),FALSE);break;
        case FALSE:
            gtk_progress_bar_set_inverted(GTK_PROGRESS_BAR(data),TRUE);break;
        default:break;
    }
}

void entry_activate(GtkWidget widget,gpointer data){
    gtk_dialog_response(GTK_DIALOG(data),GTK_RESPONSE_OK);
}

void change_text(GtkWidget *widget,gpointer data){
    //This function is for change progress bar text
    const gchar *progress_text;
    GtkWidget *dialog;
    GtkWidget *entry;
    GtkWidget *content_area;
    dialog=gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog),"Change Progress Bar Text");
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    entry=gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry),"Progress...");
    gtk_container_add(GTK_CONTAINER(content_area),entry);
    gtk_widget_show(entry);
    g_signal_connect(G_OBJECT(entry),"activate",G_CALLBACK(entry_activate),(gpointer)dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    progress_text=gtk_entry_get_text(GTK_ENTRY(entry));
    //g_print(progress_text);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(data),progress_text);
    gtk_widget_destroy(dialog);
}

int main(int argc,char *argv[]){
    GtkWidget *window;//Create objects
    GtkWidget *fixed;
    GtkWidget *btn_add;
    GtkWidget *btn_change;
    GtkWidget *btn_exit;
    GtkWidget *btn_change_text;
    GtkWidget *progress;
    gtk_init(&argc,&argv);//gtk+ initial
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);//Create a gtk window
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);//make application exit when main window destroy
    gtk_window_set_title(GTK_WINDOW(window),"gtk (15)");//window title
    gtk_window_set_default_size(GTK_WINDOW(window),300,200);//window size
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);//window position
    fixed=gtk_fixed_new();//Create a fixed container
    gtk_container_add(GTK_CONTAINER(window),fixed);//Add the container to window
    progress=gtk_progress_bar_new();//Create a progress bar and set some attributes
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress),"Hello");
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress),TRUE);
    gtk_widget_set_size_request(progress,300,30);
    gtk_fixed_put(GTK_FIXED(fixed),progress,0,5);
    btn_add=gtk_button_new_with_label("Add");//Create "Add progress" button
    gtk_widget_set_size_request(btn_add,150,40);
    gtk_fixed_put(GTK_FIXED(fixed),btn_add,0,80);
    g_signal_connect(G_OBJECT(btn_add),"clicked",G_CALLBACK(add),(gpointer)progress);
    btn_change=gtk_button_new_with_label("Change");//Create "Change orientation" button
    gtk_widget_set_size_request(btn_change,150,40);
    gtk_fixed_put(GTK_FIXED(fixed),btn_change,150,80);
    g_signal_connect(G_OBJECT(btn_change),"clicked",G_CALLBACK(change),(gpointer)progress);
    btn_change_text=gtk_button_new_with_label("Change Text");//Create "Change Progress Text" button
    gtk_widget_set_size_request(btn_change_text,150,40);
    gtk_fixed_put(GTK_FIXED(fixed),btn_change_text,0,130);
    g_signal_connect(G_OBJECT(btn_change_text),"clicked",G_CALLBACK(change_text),(gpointer)progress);
    btn_exit=gtk_button_new_with_label("Exit");//Create "Exit" button
    gtk_widget_set_size_request(btn_exit,150,40);
    gtk_fixed_put(GTK_FIXED(fixed),btn_exit,150,130);
    g_signal_connect(G_OBJECT(btn_exit),"clicked",G_CALLBACK(gtk_main_quit),NULL);
    progress=gtk_progress_bar_new();
    gtk_widget_show_all(window);//Show everything
    gtk_main();
    return 0;
}
