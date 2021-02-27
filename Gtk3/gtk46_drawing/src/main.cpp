#include <gtk/gtk.h>
#include <cstdio>

typedef struct {
    GtkWidget *draw_area1;
    double x;
    double y;
}MousePos;

static cairo_surface_t *surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,640,360);

//static double start_x,start_y;

static void
clear_surface (void)
{
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

gboolean draw_cb(GtkWidget *widget,cairo_t *cr,gpointer data){
    cairo_set_source_surface(cr,surface,0,0);
    cairo_paint(cr);
    /*
    guint width, height;
    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);
    cairo_arc (cr,
             width / 2.0, height / 2.0,
             MIN (width, height) / 2.0,
             0, 2 * G_PI);
    cairo_fill(cr);*/
    return FALSE;
}

static void draw_brush(GtkWidget *widget,double x,double y){
    cairo_t *cr;
    //Draw on the surface
    cr=cairo_create(surface);

    GdkRGBA color;
    //gdk_rgba_parse(&color,"66CCFF");
    
    //Draw and fill in color
    cairo_rectangle(cr,x-3,y-3,6,6);
    //gdk_cairo_set_source_rgba(cr,&color);
    cairo_fill(cr);

    cairo_destroy(cr);

    gtk_widget_queue_draw(widget);

}

void drag_begin(GtkGesture *gesture,double x,double y,MousePos *pos){
    pos->x=x;
    pos->y=y;
    draw_brush(pos->draw_area1,x,y);
    /*
    freopen("drag.txt","a",stdout);
    g_print("%lf %lf\n",x,y);
    fclose(stdout);
    */
}

void drag_update(GtkGesture *gesture,double x,double y,MousePos *pos){
    draw_brush(pos->draw_area1,x+pos->x,y+pos->y);
    /*
    freopen("drag.txt","a",stdout);
    g_print("%lf %lf\n",x+pos->x,y+pos->y);
    fclose(stdout);
    */
}

void drag_end(GtkGesture *gesture,double x,double y,MousePos *pos){
    draw_brush(pos->draw_area1,x+pos->x,y+pos->y);
    /*
    freopen("drag.txt","a",stdout);
    g_print("%lf %lf\n",x+pos->x,y+pos->y);
    fclose(stdout);
    */
}

void pressed(GtkGestureMultiPress *gesture,int n_press,double x,double y,GtkWidget *widget){
    clear_surface();
    gtk_widget_queue_draw(widget);
    /*
    g_print("%d\n",n_press);
    freopen("drag.txt","w",stdout);
    printf("\0");
    fclose(stdout);
    */
}

void close_window(void){
    if(surface){
        cairo_surface_destroy(surface);
    }
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*draw_area;
    GtkGesture *press,*drag;
    //Create a window
    window=gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"Mouse Event Test");
    gtk_window_set_default_size(GTK_WINDOW(window),640,360);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");

    g_signal_connect(window,"destroy",G_CALLBACK(close_window),NULL);

    //Create a draw area
    draw_area=gtk_drawing_area_new();
    g_signal_connect(draw_area,"draw",G_CALLBACK(draw_cb),NULL);
    //Create gestures

    static MousePos pos;
    pos.draw_area1=draw_area;
    //"Drag" gesture
    drag=gtk_gesture_drag_new(draw_area);
    
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(drag),GDK_BUTTON_PRIMARY);
    g_signal_connect(drag,"drag-begin",G_CALLBACK(drag_begin),&pos);
    g_signal_connect(drag,"drag-update",G_CALLBACK(drag_update),&pos);
    g_signal_connect(drag,"drag-end",G_CALLBACK(drag_end),&pos);

    //"Press" gesture

    press=gtk_gesture_multi_press_new(draw_area);

    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(press),GDK_BUTTON_SECONDARY);
    g_signal_connect(press,"pressed",G_CALLBACK(pressed),draw_area);

    gtk_container_add(GTK_CONTAINER(window),draw_area);
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
