#pragma once

#include <gtkmm.h>

class MineCell : public Gtk::Button
{
public:
    bool is_mine = false;
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
    MineCell cell[49];

    // Timer
    sigc::connection mytimer;

    // Signal Handlers
    void reset_game();
    void cell_clicked(MineCell *cell);
};
