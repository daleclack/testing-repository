#include "MineSweeper.hh"

MineSweeper::MineSweeper()
{
    // Initalize Window
    set_title("Gtkmm MineSweeper");
    set_icon_name("org.gtk.daleclack");

    // Append buttons to grid
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cell[i * 7 + j].set_label("?");
            cell[i * 7 + j].signal_clicked().connect(sigc::bind(
                sigc::mem_fun(*this, &MineSweeper::cell_clicked), &cell[i * 7 + j]));
            mine_grid.attach(cell[i * 7 + j], j, i);
        }
    }

    // Show everything
    add(mine_grid);
    show_all_children();
}

void MineSweeper::reset_game()
{
    // Append item
}

void MineSweeper::cell_clicked(MineCell *cell)
{
    
}
