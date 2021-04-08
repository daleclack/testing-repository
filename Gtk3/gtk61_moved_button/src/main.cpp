#include <gtk/gtk.h>
#include <ctime>

gboolean move_btn(gpointer data){
    GObject *fixed,*btn1,*win;
    int width,height,x,y;
    double x1,y1;
    srand((unsigned)time(NULL));
    x1=(rand()%10)/10.0;
    y1=(rand()%10)/10.0;
    //g_print("%f %f\n",x1,y1);

    GtkBuilder *builder=GTK_BUILDER(data);
    fixed=gtk_builder_get_object(builder,"fixed");
    btn1=gtk_builder_get_object(builder,"btn1");

    win=gtk_builder_get_object(builder,"window1");
    gtk_window_get_size(GTK_WINDOW(win),&width,&height);
    x=x1*width;y=y1*height;
    //g_print("%d %d\n",x,y);
    if(x>440||y>250){
        g_print("ERROR");
        return FALSE;
    }
    gtk_fixed_move(GTK_FIXED(fixed),GTK_WIDGET(btn1),x,y);

    return TRUE;
}

static void button_entered(GtkWidget *widget,GtkBuilder *builder){
    GObject *fixed,*win;
    int width,height,x,y;
    double x1,y1;
    srand((unsigned)time(NULL));
    x1=(rand()%10)/10.0;
    y1=(rand()%10)/10.0;

    //Get window size and position
    win=gtk_builder_get_object(builder,"window1");
    gtk_window_get_size(GTK_WINDOW(win),&width,&height);
    x=x1*width;y=y1*height;
    fixed=gtk_builder_get_object(builder,"fixed");
    gtk_fixed_move(GTK_FIXED(fixed),widget,x,y);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkBuilder *builder,*menumodel1;
    GObject *window,*popover,*btn1,*btn2,*btn3;

    //Get window
    builder=gtk_builder_new_from_resource("/gtk61/window.ui");
    window=gtk_builder_get_object(builder,"window1");

    //Button:move when click the button
    btn1=gtk_builder_get_object(builder,"btn1");
    g_signal_connect(btn1,"clicked",G_CALLBACK(button_entered),builder);
    btn2=gtk_builder_get_object(builder,"btn2");
    g_signal_connect(btn2,"clicked",G_CALLBACK(button_entered),builder);
    btn3=gtk_builder_get_object(builder,"btn3");
    g_signal_connect(btn3,"clicked",G_CALLBACK(button_entered),builder);

    g_timeout_add(1000,move_btn,builder);

    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}