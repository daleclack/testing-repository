#pragma once

#include <gtkmm.h>
#include "InputBox.hh"
#include "ScoresWin.hh"

// The status of the minesweeper game
enum class GameStatus
{
    Running,
    Winned,
    Ended,
    Paused
};

// The cell of the minesweeper game,
// and the mines is under the cell
class MineCell : public Gtk::Button
{
public:
    bool has_mine = false; // Whether the grid has mine
    bool cleared = false;  // Whether the mine is cleared
    int mines_around;      // The number near the grid
    int x, y;              // The Position of the grid
    MineCell()
    {
        // Set button style
        mines_around = 0;
    }
};

// Main class
class MineSweeper : public Gtk::ApplicationWindow
{
public:
    MineSweeper();
    ~MineSweeper();

private:
    // HeaderBar
    Gtk::HeaderBar header;
    Gtk::MenuButton menu_btn;
    Gtk::PopoverMenu popover1;

    // Child widgets
    Gtk::Grid mine_grid;
    Gtk::Label status_label;
    Gtk::Box main_box, btn_box;
    Gtk::Button btnstart, btnpause, btnshow, btnexit;

    // The cell to place mines
    MineCell *cell;
    GameStatus game_status; // Use enum class for the status of game
    // bool winned, game_ended;     // The status of game(win/end)
    int mines_clear, mine_count; // Whether the mine is cleared

    // Menu
    Glib::RefPtr<Gtk::Builder> menu_builder;

    // Timer
    int timer_count;
    sigc::connection mytimer;

    // Input dialog
    InputBox *input_dialog;

    // Scores Window
    ScoresWin *scores_win;

    // Signal Handlers
    void new_game();                                               // "New Game" handler
    void reset_game(int width = 7, int height = 7, int mines = 9); // Reset all mines
    void pause_game();                                             // Pause or continue the game
    void calc_mines();                                             // Get the mines around
    void show_mines();                                             // Show all mines
    void show_scores();                                            // Show all scores
    void game_lost(int explode_index);                             // You lost the game
    void cell_clicked(MineCell *cell1);                            // Open a cell
    bool timer_func();                                             // Timer
    void check_mines(int pos_x, int pos_y);                        // Check if there is a mine
};
