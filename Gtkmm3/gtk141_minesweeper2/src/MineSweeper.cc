#include "MineSweeper.hh"
#include <string>

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
    // Reset timer
    mytimer.disconnect();
    timer_count = 0;
    mytimer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &MineSweeper::timer_func), 1000);

    mine_count = 0;
    // Reset all data
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            //cell[i * 7 + j].set_label("?");
            cell[i * 7 + j].set_image_from_icon_name("");
            cell[i * 7 + j].set_always_show_image();
            cell[i * 7 + j].mines_around = 0;
            cell[i * 7 + j].has_mine = false;
            cell[i * 7 + j].cleared = false;
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
    // std::cout << mine_count << std::endl;
    game_ended = false;
    winned = true;
    status_label.set_label(" ");
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
            cell[i].set_image_from_icon_name("mine");
        }
    }
}

bool MineSweeper::timer_func(){
    // Set timer
    char tmp[50];
    timer_count++;
    sprintf(tmp, "Time:%d", timer_count);
    status_label.set_label(tmp);
    return true;
}

void MineSweeper::cell_clicked(MineCell *cell)
{
    if (!game_ended && !cell->cleared)
    {
        cell->cleared = true;
        // If get mine, the game will end now
        if (cell->has_mine)
        {
            // Set game to stop
            winned = false;
            show_mines();
            status_label.set_label("You lost!");
            game_ended = true;
            mytimer.disconnect();
        }
        else
        {
            mines_clear++;
            // std::cout << mines_clear << std::endl;
            if (cell->mines_around == 0)
            {
                // cell->set_label(" ");
                cell->set_image_from_icon_name("");
            }
            else
            {
                char *label = g_strdup_printf("%dmines", cell->mines_around);
                cell->set_image_from_icon_name(label);
                g_free(label);
            }
        }

        // If all the mines has cleared, you has winned
        if (mines_clear == 40)
        {
            // Stop the game
            status_label.set_label("You winned!");
            winned = true;
            game_ended = true;
            mytimer.disconnect();

            // Save the time of game
            
        }
    }
}
