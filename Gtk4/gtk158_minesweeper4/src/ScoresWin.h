#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(ScoresWin, scores_win, Scores, Win, GtkWindow)

ScoresWin *scores_win_new(GtkWindow *parent);

void scores_win_update_and_show(ScoresWin *self);
