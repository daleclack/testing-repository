#include <gtk/gtk.h>
#include <cstdio>

typedef struct {
    double x;
    double y;
}MousePos;

//static double start_x,start_y;

void drag_begin(GtkGesture *gesture,double x,double y,MousePos *pos){
    pos->x=x;
    pos->y=y;
    freopen("drag.txt","a",stdout);
    g_print("%lf %lf\n",x,y);
    fclose(stdout);
}

void drag_update(GtkGesture *gesture,double x,double y,MousePos *pos){
    freopen("drag.txt","a",stdout);
    g_print("%lf %lf\n",x+pos->x,y+pos->y);
    fclose(stdout);
}

void drag_end(GtkGesture *gesture,double x,double y,MousePos *pos){
    freopen("drag.txt","a",stdout);
    g_print("%lf %lf\n",x+pos->x,y+pos->y);
    fclose(stdout);
}

void pressed(GtkGestureMultiPress *gesture,int n_press,double x,double y,gpointer user_data){
    g_print("%d\n",n_press);
    freopen("drag.txt","w",stdout);
    printf("\0");
    fclose(stdout);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window;
    GtkGesture *press,*drag;
    //Create a window
    window=gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"Mouse Event Test");
    gtk_window_set_default_size(GTK_WINDOW(window),640,360);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    //Create gestures

    static MousePos pos;
    //"Drag" gesture
    drag=gtk_gesture_drag_new(window);
    
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(drag),GDK_BUTTON_PRIMARY);
    g_signal_connect(drag,"drag-begin",G_CALLBACK(drag_begin),&pos);
    g_signal_connect(drag,"drag-update",G_CALLBACK(drag_update),&pos);
    g_signal_connect(drag,"drag-end",G_CALLBACK(drag_end),&pos);

    //"Press" gesture

    press=gtk_gesture_multi_press_new(window);

    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(press),GDK_BUTTON_SECONDARY);
    g_signal_connect(press,"pressed",G_CALLBACK(pressed),NULL);

    gtk_widget_show_all(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    return status;
}
