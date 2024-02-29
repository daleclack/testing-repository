#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(ScoresItem, scores_item, Scores, Item, GObject)

ScoresItem *scores_item_new(const char *win_name, int win_time);

const char *scores_item_get_name(ScoresItem *item);

void scores_item_set_name(ScoresItem *item, const char *win_name);

int scores_item_get_time(ScoresItem *item);

void scores_item_set_time(ScoresItem *item, int win_time);
