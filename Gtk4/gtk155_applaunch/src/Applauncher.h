#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(AppLauncher, app_launcher, APP, LAUNCHER, GtkApplicationWindow)

AppLauncher *app_launcher_new(GtkApplication *app);
