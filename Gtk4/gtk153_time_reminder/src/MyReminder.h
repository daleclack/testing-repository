#pragma once

#include <gtk/gtk.h>
#include "../json_nlohmann/json.hpp"

using json = nlohmann::json;

G_DECLARE_FINAL_TYPE(MyReminder, my_reminder, MY, REMINDER, GtkApplicationWindow)

MyReminder *my_reminder_new(GtkApplication *app);
