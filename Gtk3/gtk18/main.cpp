#include <gtk/gtk.h>

void print1(GtkWidget *widget,gpointer data){
//Check user selection of combo box and print specific char
    const gchar *str=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data));
    g_print("%s\n",str);
    if(strcmp(str,"test1")==0){
        g_print("1\n");
    }else{
        g_print("2\n");
    }
}

static void activate(GtkApplication *app,gpointer user_data){
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *combo;
    GtkWidget *button;
    window=gtk_application_window_new(app);//Create a window sized 300x200
    gtk_window_set_title(GTK_WINDOW(window),"gtk (18)");
    gtk_window_set_default_size(GTK_WINDOW(window),300,200);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed=gtk_fixed_new();//Put the widget at a fixed position
    gtk_container_add(GTK_CONTAINER(window),fixed);
    combo=gtk_combo_box_text_new();//Create a combo box
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),"test1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),"test2");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo),0);//Set default selection
    gtk_widget_set_size_request(combo,100,40);
    gtk_fixed_put(GTK_FIXED(fixed),combo,100,50);
    button=gtk_button_new_with_label("Print");//Button to response
    gtk_widget_set_size_request(button,100,50);
    gtk_fixed_put(GTK_FIXED(fixed),button,100,105);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(print1),(gpointer)combo);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[]){
//Common way to create a gtk application
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.daleclack.gtk18",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
