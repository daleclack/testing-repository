#pragma once

#include <gtkmm.h>

class MineCell : public Gtk::Button
{
public:
    bool has_mine = false;
    int mines_around;
    MineCell(){
        // Set button style
        set_relief(Gtk::RELIEF_NONE);
    }
};

class MineSweeper : public Gtk::ApplicationWindow
{
public:
    MineSweeper();

private:
    // Child widgets
    Gtk::Grid mine_grid;
    Gtk::Label status_label;
    Gtk::Box main_box, btn_box;
    MineCell cell[49];
    bool winned, game_ended;
    int mines_clear, mine_count;

    // Timer
    sigc::connection mytimer;

    // Signal Handlers
    void reset_game();
    void cell_clicked(MineCell *cell);
};
