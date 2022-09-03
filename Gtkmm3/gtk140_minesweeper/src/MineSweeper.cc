#include "MineSweeper.hh"
#include <string>
#include <fstream>

MineSweeper::MineSweeper()
    : main_box(Gtk::ORIENTATION_VERTICAL, 5),
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

    // Buttons
    btnstart.set_label("Start/Reset");
    btnshow.set_label("Show All");
    btnexit.set_label("Exit");
    btn_box.pack_start(btnstart, Gtk::PACK_SHRINK);
    btn_box.pack_start(btnshow, Gtk::PACK_SHRINK);
    btn_box.pack_start(btnexit, Gtk::PACK_SHRINK);
    btnstart.signal_clicked().connect(sigc::mem_fun(*this, &MineSweeper::reset_game));
    btnshow.signal_clicked().connect(sigc::mem_fun(*this, &MineSweeper::show_mines));
    btnexit.signal_clicked().connect(sigc::mem_fun(*this, &MineSweeper::hide));

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
            cell[i * 7 + j].mines_around = 0;
        }
    }

    // Reset mines
    while (mine_count < 9)
    {
        int index = g_random_int_range(0, 49);
        if (!(cell[index].has_mine))
        {
            cell[index].has_mine = true;
            // cell[index].set_label("x");
            mine_count++;
        }
    }
    game_ended = false;
    winned = true;
    calc_mines();
}

void MineSweeper::calc_mines()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            // std::fstream outfile;
            // outfile.open("test.txt", std::ios_base::app);
            // if (outfile.is_open())
            // {
            //     outfile << "Start:" << i << " " << j << std::endl;
            //     outfile << "index1:" << MAX(0, i - 1) << " " << MIN(i + 1, 6) << std::endl;
            //     outfile << "index2:" << MAX(0, j - 1) << " " << MIN(j + 1, 6) << std::endl;
            // }
            // outfile.close();
            int index1, index2;
            for (index1 = MAX(0, i - 1); index1 < MIN(i + 1, 6) + 1; index1++)
            {
                for (index2 = MAX(0, j - 1); index2 < MIN(j + 1, 6) + 1; index2++)
                {
                    if ((cell[index1 * 7 + index2].has_mine))
                    {
                        // std::fstream outfile;
                        // outfile.open("test.txt", std::ios_base::app);
                        // if (outfile.is_open())
                        // {
                        //     outfile << index1 << " " << index2 << "Has mine!" << std::endl;
                        // }
                        // outfile.close();
                        cell[i * 7 + j].mines_around++;
                    }
                }
            }
            // if (!cell[i * 7 + j].has_mine)
            // {
            //
            // }
        }
    }
}

void MineSweeper::show_mines(){
    for(int i = 0; i < 49; i++){
        if(cell[i].has_mine){
            cell[i].set_label("x");
        }
    }
}

void MineSweeper::cell_clicked(MineCell *cell)
{
    if (!game_ended)
    {
        // If get mine, the game will end now
        if (cell->has_mine)
        {
            winned = false;
            show_mines();
            status_label.set_label("You lost!");
            game_ended = true;
        }
        else
        {
            mines_clear++;
            if (cell->mines_around == 0)
            {
                cell->set_label(" ");
            }
            else
            {
                char *label = g_strdup_printf("%d", cell->mines_around);
                cell->set_label(label);
                g_free(label);
            }
        }

        // If all the mines has cleared, you has winned
        if (mines_clear == 40)
        {
            status_label.set_label("You winned!");
            winned = true;
            game_ended = true;
        }
    }
}
