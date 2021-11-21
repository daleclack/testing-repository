#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MyImage,my_image,MY,IMAGE,GtkWidget)

GtkWidget * my_image_new();

void my_image_set_pixbuf(MyImage * self, GdkPixbuf * pixbuf);
