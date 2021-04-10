#include <gtk/gtk.h>

/*void change_update(GtkWidget *widget,GtkBuilder *builder){
    //Get scale widgets
    GObject *scale1=gtk_builder_get_object(builder,"scale1");
    GObject *scale2=gtk_builder_get_object(builder,"scale2");
    
}*/

void show_value(GtkWidget *widget,GtkBuilder *builder){
    //Get scale widgets
    GObject *scale1=gtk_builder_get_object(builder,"scale1");
    GObject *scale2=gtk_builder_get_object(builder,"scale2");
    //Get checkbutton status and set scale widgets
    //gboolean checked=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
    gboolean checked=gtk_check_button_get_active((GtkCheckButton*)widget);
    gtk_scale_set_draw_value(GTK_SCALE(scale1),checked);
    gtk_scale_set_draw_value(GTK_SCALE(scale2),checked);
}

void change_pos(GtkWidget *widget,GtkBuilder *builder){
    //Get scale widgets
    GObject *scale1=gtk_builder_get_object(builder,"scale1");
    GObject *scale2=gtk_builder_get_object(builder,"scale2");
    //Get selection and set the value position
    gint pos=gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
    //g_print("%d\n",pos);
    GtkPositionType position;
    switch(pos){
        case 0:
            position=GTK_POS_TOP;
            break;
        case 1:
            position=GTK_POS_BOTTOM;
            break;
        case 2:
            position=GTK_POS_LEFT;
            break;
        case 3:
            position=GTK_POS_RIGHT;
            break;
    }
    gtk_scale_set_value_pos(GTK_SCALE(scale1),position);
    gtk_scale_set_value_pos(GTK_SCALE(scale2),position);
}

void change_digit(GtkWidget *widget,GtkBuilder *builder){
    //Get scale widgets
    GObject *scale1=gtk_builder_get_object(builder,"scale1");
    GObject *scale2=gtk_builder_get_object(builder,"scale2");
    gint digits=gtk_range_get_value(GTK_RANGE(widget));
    //Set the scale digits
    gtk_scale_set_digits(GTK_SCALE(scale1),digits);
    gtk_scale_set_digits(GTK_SCALE(scale2),digits);
}

void page_size(GtkWidget *widget,GtkBuilder *builder){
    GObject *set=gtk_builder_get_object(builder,"adjustment1");
    gdouble page_size;
    page_size=gtk_range_get_value(GTK_RANGE(widget));
    gtk_adjustment_set_page_size(GTK_ADJUSTMENT(set),page_size);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Main window
    GtkBuilder *builder=gtk_builder_new_from_resource("/gtk39/window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    //GdkPixbuf *pixbuf=gdk_pixbuf_new_from_resource("/gtk39/icon.jpg",NULL);
    //gtk_window_set_icon(GTK_WINDOW(window),pixbuf);
    gtk_window_set_icon_name(GTK_WINDOW(window),"icon1");
    gtk_application_add_window(app,GTK_WINDOW(window));
    //Show value setting
    GObject *btn_show=gtk_builder_get_object(builder,"btnshow");
    g_signal_connect(btn_show,"toggled",G_CALLBACK(show_value),builder);
    //Update policy settings,Gtk3 deprecated

    //Scale Value Position Settings
    GObject *combo_pos=gtk_builder_get_object(builder,"combo_pos");
    g_signal_connect(combo_pos,"changed",G_CALLBACK(change_pos),builder);
    //Scale Digits settings
    GObject *digit_scale=gtk_builder_get_object(builder,"digit_scale");
    g_signal_connect(digit_scale,"value-changed",G_CALLBACK(change_digit),builder);
    //Scroll bar page setting
    GObject *size_scale=gtk_builder_get_object(builder,"size_scale");
    g_signal_connect(size_scale,"value-changed",G_CALLBACK(page_size),builder);
    //"Exit" button
    GObject *btn_exit=gtk_builder_get_object(builder,"btnexit");
    g_signal_connect_swapped(btn_exit,"clicked",G_CALLBACK(gtk_window_destroy),window);
    gtk_widget_show(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
