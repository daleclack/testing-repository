#pragma once

#include <gtkmm.h>

class MineCell : public Gtk::Button
{
public:
    bool has_mine = false;  // Whether the grid has mine
    bool cleared = false;   // Whether the mine is cleared
    int mines_around;       // The number near the grid
    int x, y;               // The Position of the grid
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
    MineCell *cell;
    bool winned, game_ended;
    int mines_clear, mine_count;

    // Timer
    int timer_count;
    sigc::connection mytimer;

    // Signal Handlers
    void reset_game();
    void calc_mines();
    void show_mines();
    void game_lost(int explode_index);
    void cell_clicked(MineCell *cell1);
    bool timer_func();
    void check_mines(int pos_x, int pos_y);
};
