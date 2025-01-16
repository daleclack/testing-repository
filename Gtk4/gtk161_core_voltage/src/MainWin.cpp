#include "MainWin.h"
#include "CoreVolt.h"
#include <thread>

struct _MainWin{
    GtkApplicationWindow parent_instance;
    GtkWidget *label_maxvolt, *label_currvolt, *label_info1, *label_info2;
    GtkWidget *main_frame;
    GtkWidget *volt_grid;
};

G_DEFINE_TYPE(MainWin, main_win, GTK_TYPE_APPLICATION_WINDOW)

static char max_volt[10], curr_volt[10];

gboolean core_volt_func(gpointer data){
    MainWin *self = Main_Win(data);

    // Update core voltage values to the labels
    // get_core_voltage(curr_volt, max_volt);
    gtk_label_set_text(GTK_LABEL(self->label_maxvolt), max_volt);
    gtk_label_set_text(GTK_LABEL(self->label_currvolt), curr_volt);

    return TRUE;
}

static gboolean main_win_close(GtkWindow *self, gpointer data)
{
    // Close the thread
    stop_voltage_monitoring();

    // Destroy the window
    gtk_window_destroy(self);
    return TRUE;
}

static void main_win_init(MainWin *self){
    GtkWindow *win = GTK_WINDOW(self);
    // Initialize window properties
    gtk_window_set_title(win, "Core Voltage Monitor");
    gtk_window_set_default_size(win, 250, 200);
    gtk_window_set_icon_name(win, "org.gtk.daleclack");

    // Add widgets to window
    self->volt_grid = gtk_grid_new();
    self->main_frame = gtk_frame_new(NULL);
    gtk_frame_set_label_widget(GTK_FRAME(self->main_frame), gtk_label_new("Core Voltage Information"));
    gtk_widget_set_valign(GTK_WIDGET(self->main_frame), GTK_ALIGN_CENTER);
    self->label_info1 = gtk_label_new("Max Core Voltage: ");
    self->label_info2 = gtk_label_new("Current Core Voltage: ");
    self->label_maxvolt = gtk_label_new("0.00 V");
    self->label_currvolt = gtk_label_new("0.00 V");
    gtk_grid_attach(GTK_GRID(self->volt_grid), self->label_info1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(self->volt_grid), self->label_maxvolt, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(self->volt_grid), self->label_info2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(self->volt_grid), self->label_currvolt, 1, 1, 1, 1);
    gtk_frame_set_child(GTK_FRAME(self->main_frame), self->volt_grid);
    gtk_window_set_child(win, self->main_frame);
    g_timeout_add(1000, core_volt_func, self);

    // Use a thread to update core voltage values every second
    std::thread t(get_core_voltage, curr_volt, max_volt);
    t.detach();
}

static void main_win_class_init(MainWinClass *klass){
}

// Create a new MainWin
MainWin *main_win_new(GtkApplication *app){
    return Main_Win(g_object_new(MAIN_WIN_TYPE, "application", app, NULL));
}