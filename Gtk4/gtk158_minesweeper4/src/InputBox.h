#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(InputBox, input_box, Input, Box, GtkWindow)

InputBox *input_box_new(GtkWindow *parent);

void input_box_set_game_time(InputBox *self, int time);

void input_box_present(InputBox *self);

void input_box_show_scores(InputBox *self);
