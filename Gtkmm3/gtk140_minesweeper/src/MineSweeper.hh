#pragma once

#include <gtkmm.h>
#include "InputBox.hh"

class MineCell : public Gtk::Button
{
public:
    bool has_mine = false;
    bool cleared = false;
    int mines_around;
    MineCell(){
        // Set button style
        set_relief(Gtk::RELIEF_NONE);
        mines_around = 0;
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
    Gtk::Button btnstart, btnshow, btnexit;
    MineCell cell[49];
    bool winned, game_ended;
    int mines_clear, mine_count;

    // Timer
    int timer_count;
    sigc::connection mytimer;

    // When winned, show a input box
    InputBox win_input;

    // Signal Handlers
    void reset_game();
    void calc_mines();
    void show_mines();
    void cell_clicked(MineCell *cell);
    bool timer_func();
};
