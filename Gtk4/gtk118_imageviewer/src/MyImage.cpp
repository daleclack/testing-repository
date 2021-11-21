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
            g_value_set_object(value,&self->scale);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,spec);
            break;
    }
}

static void my_image_snapshot(GtkWidget * widget,GtkSnapshot * snapshot){
    g_print("Widget Snapshoted");
}

static void my_image_init(MyImage * self){
    self->scale = 1.f;
    gtk_widget_init_template(GTK_WIDGET(self));
}

static void my_image_class_init(MyImageClass * self_class){
    GObjectClass * object_class = G_OBJECT_CLASS(self_class);
    GtkWidgetClass * widget_class = GTK_WIDGET_CLASS(self_class);

    object_class->dispose = my_image_dispose;
    object_class->set_property = my_image_set_property;
    object_class->get_property = my_image_get_property;

    widget_class->snapshot = my_image_snapshot;

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

    //Bind Childs
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(self_class),MyImage,menu);
    gtk_widget_class_bind_template_callback(self_class,pressed_cb);
}

GtkWidget * my_image_new(){
    return (GtkWidget*)g_object_new(my_image_get_type(),NULL);
}
