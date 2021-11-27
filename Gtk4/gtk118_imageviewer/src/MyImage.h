#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MyImage,my_image,MY,IMAGE,GtkWidget)

GtkWidget * my_image_new();

void my_image_set_pixbuf(MyImage * self, GdkPixbuf * pixbuf);

void my_image_bind_adjustments(MyImage       * self, 
                               GtkAdjustment * hadjustment1, 
                               GtkAdjustment * vadjustment1);

static inline double my_adjustment_get_max_value(GtkAdjustment * adjustment){
    return (gtk_adjustment_get_upper(adjustment)-gtk_adjustment_get_page_size(adjustment));
}
