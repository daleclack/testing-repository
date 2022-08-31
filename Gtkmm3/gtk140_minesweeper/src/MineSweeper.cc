#include "MineSweeper.hh"
#include <string>

MineSweeper::MineSweeper()
:main_box(Gtk::ORIENTATION_VERTICAL, 5),
btn_box(Gtk::ORIENTATION_HORIZONTAL, 5)
{
    // Initalize Window
    set_title("Gtkmm MineSweeper");
    set_icon_name("org.gtk.daleclack");

    // Append buttons to grid
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            // cell[i * 7 + j].set_label("?");
            cell[i * 7 + j].signal_clicked().connect(sigc::bind(
                sigc::mem_fun(*this, &MineSweeper::cell_clicked), &cell[i * 7 + j]));
            mine_grid.attach(cell[i * 7 + j], j, i);
        }
    }

    // Default setting
    reset_game();

    // Pack widgets
    status_label.set_halign(Gtk::ALIGN_CENTER);
    btn_box.set_halign(Gtk::ALIGN_CENTER);
    main_box.pack_start(status_label, Gtk::PACK_SHRINK);
    main_box.pack_start(mine_grid);
    main_box.pack_start(btn_box, Gtk::PACK_SHRINK);

    // Show everything
    add(main_box);
    show_all_children();
}

void MineSweeper::reset_game()
{
    mine_count = 0;
    // Reset all data
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cell[i * 7 + j].set_label("?");
        }
    }

    // Reset mines
    while(mine_count < 9)
    {
        int index = g_random_int_range(0, 49);
        if(!(cell[index].has_mine)){
            cell[index].has_mine = true;
            cell[index].set_label("x");
            mine_count++;
        } 
    }
    game_ended = false;
    winned = true;
}

void MineSweeper::cell_clicked(MineCell *cell)
{
    if (!game_ended)
    {
        // If get mine, the game will end now
        if (cell->has_mine)
        {
            winned = false;
            game_ended = true;
        }
        else
        {
            mines_clear++;
            cell->set_label(" ");
        }

        // If all the mines has cleared, you has winned
        if (mines_clear == 40)
        {
            winned = true;
            game_ended = true;
        }
    }
}
