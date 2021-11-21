#include "MyImage.h"

enum{
    PROP_PAINTABLE = 1,
    PROP_SCALE
};

struct _MyImage{
    GtkWidget parent_instance;

    GdkPaintable * paintable;
    float scale;

    GtkWidget * menu;
};

struct _MyImageClass{
    GtkWidgetClass parent_class;
};

G_DEFINE_TYPE(MyImage,my_image,GTK_TYPE_WIDGET)

void my_image_set_pixbuf(MyImage * self, GdkPixbuf * pixbuf){
    //g_clear_object(&self->paintable);
    self->paintable = (GdkPaintable*)gdk_texture_new_for_pixbuf(pixbuf);
}

static void pressed_cb(GtkGestureClick * gesture,int n_press,double x,double y,MyImage * self){
    //Show Menu in the position of mouse
    GdkRectangle pos = {(int)x,(int)y,1,1};
    gtk_popover_set_pointing_to(GTK_POPOVER(self->menu),&pos);

    gtk_popover_popup(GTK_POPOVER(self->menu));
}

static void my_image_dispose(GObject * object){
    //Deconstructer
    MyImage * self = MY_IMAGE(object);
    
    g_clear_object(&self->paintable);
    g_clear_pointer(&self->menu,gtk_widget_unparent);

    G_OBJECT_CLASS(my_image_parent_class)->dispose(object);
}

static void my_image_measure(GtkWidget      *widget,
                             GtkOrientation  orientation,
                             int             for_size,
                             int            *minimum,
                             int            *natural,
                             int            *minimum_baseline,
                             int            *natural_baseline)
{
    MyImage * self = MY_IMAGE(widget);
    int size;

    //Measure size
    if(orientation == GTK_ORIENTATION_HORIZONTAL){
        size = gdk_paintable_get_intrinsic_width(GDK_PAINTABLE(self->paintable));
    }else{
        size = gdk_paintable_get_intrinsic_height(GDK_PAINTABLE(self->paintable));
    }

    *minimum = *natural = self->scale * size;
}

static void my_image_size_allocate(GtkWidget * widget,int width,int height,int baseline){

    MyImage * self = MY_IMAGE(widget);
    /* Since we are not using a layout manager (who would do this
     * for us), we need to allocate a size for our menu by calling
     * gtk_popover_present().
     */
    gtk_popover_present(GTK_POPOVER(self->menu));
}

static void my_image_set_property(GObject * object,guint property_id,
                                  const GValue * value,GParamSpec * spec)
{
    MyImage * self = MY_IMAGE(object);

    //Set new value for property
    switch(property_id){
        case PROP_PAINTABLE:
            g_clear_object(&self->paintable);
            self->paintable = (GdkPaintable*)g_value_dup_object(value);
            gtk_widget_queue_resize(GTK_WIDGET(object));
            break;

        case PROP_SCALE:
            self->scale = g_value_get_float(value);
            gtk_widget_queue_resize(GTK_WIDGET(object));
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,spec);
            break;
    }
}

static void my_image_get_property(GObject * object,guint property_id,
                                  GValue * value,GParamSpec * spec)
{
    MyImage * self = MY_IMAGE(object);

    //Get the value
    switch(property_id){
        case PROP_PAINTABLE:
            g_value_set_object(value,self->paintable);
            break;

        case PROP_SCALE:
            g_value_set_float(value,self->scale);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,spec);
            break;
    }
}

static void my_image_snapshot(GtkWidget * widget,GtkSnapshot * snapshot){
    MyImage * self = MY_IMAGE(widget);
    int x,y,width,height;
    double w,h;

    //Get size for window
    width = gtk_widget_get_width(widget);
    height = gtk_widget_get_height(widget);

    //Get size for paintable
    w = self->scale * gdk_paintable_get_intrinsic_width(GDK_PAINTABLE(self->paintable));
    h = self->scale * gdk_paintable_get_intrinsic_height(GDK_PAINTABLE(self->paintable));

    //Get position
    x=MAX(0,(width - ceil(w)) / 2);
    y=MAX(0,(height - ceil(h)) / 2);

    //Make a snapshot
    graphene_rect_t rect = {0,0,(float)width,(float)height};
    graphene_point_t point = {(float)x,(float)y};
    gtk_snapshot_push_clip(snapshot,&rect);
    gtk_snapshot_save(snapshot);
    gtk_snapshot_translate(snapshot,&point);
    gdk_paintable_snapshot(GDK_PAINTABLE(self->paintable),snapshot,w,h);
    gtk_snapshot_restore(snapshot);
    gtk_snapshot_pop(snapshot);
}

static void zoom_cb(GtkWidget * widget,const char * action_name,GVariant * parmeter){
    MyImage * self = MY_IMAGE(widget);
    float scale = self->scale;

    //Zoom in or zoom out the image
    if(g_str_equal(action_name,"zoom.in")){
        scale = MIN(10 , self->scale * M_SQRT2);
    }else if(g_str_equal(action_name,"zoom.out")){
        scale = MAX(0, self->scale / M_SQRT2);
    }else{
        scale = 1.0;
    }

    gtk_widget_action_set_enabled (widget, "zoom.in", scale < 10);
    gtk_widget_action_set_enabled (widget, "zoom.out", scale > 0.01);
    gtk_widget_action_set_enabled (widget, "zoom.reset", scale != 1);

    g_object_set (widget, "scale", scale, NULL);
}

static void my_image_init(MyImage * self){
    self->scale = 1.f;
    gtk_widget_init_template(GTK_WIDGET(self));
}

static void my_image_class_init(MyImageClass * self_class){
    GObjectClass * object_class = G_OBJECT_CLASS(self_class);
    GtkWidgetClass * widget_class = GTK_WIDGET_CLASS(self_class);

    //Link Function pointers
    object_class->dispose = my_image_dispose;
    object_class->set_property = my_image_set_property;
    object_class->get_property = my_image_get_property;

    widget_class->snapshot = my_image_snapshot;
    widget_class->size_allocate = my_image_size_allocate;
    widget_class->measure = my_image_measure;

    //Add a property for paintable widget
    g_object_class_install_property(object_class,PROP_PAINTABLE,
                                    g_param_spec_object("paintable","Paintable","Paintable",
                                    GDK_TYPE_PAINTABLE,G_PARAM_READWRITE));

    //Property for scale number
    g_object_class_install_property(object_class,PROP_SCALE,
                                    g_param_spec_float("scale","Scale","Scale",
                                    0.0,10.0,1.0,G_PARAM_READWRITE));

    //Initalize Template
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(self_class),
                                                "/org/gtk/daleclack/MyImage.ui");

    /* These are the actions that we are using in the menu */
    gtk_widget_class_install_action (widget_class, "zoom.in", NULL, zoom_cb);
    gtk_widget_class_install_action (widget_class, "zoom.out", NULL, zoom_cb);
    gtk_widget_class_install_action (widget_class, "zoom.reset", NULL, zoom_cb);

    //Bind Childs
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(self_class),MyImage,menu);
    gtk_widget_class_bind_template_callback(self_class,pressed_cb);
}

GtkWidget * my_image_new(){
    return (GtkWidget*)g_object_new(my_image_get_type(),NULL);
}
