#include "MineSweeper.hh"
#include <string>
#include <iostream>

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
            cell[i * 7 + j].set_relief(Gtk::RELIEF_HALF);
            cell[i * 7 + j].x = j;
            cell[i * 7 + j].y = i;
            cell[i * 7 + j].cleared = false;
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
    mine_grid.set_halign(Gtk::ALIGN_CENTER);
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
    mines_clear = 0;
    // Reset all data
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            // cell[i * 7 + j].set_label("?");
            cell[i * 7 + j].set_relief(Gtk::RELIEF_HALF);
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
            // std::fstream outfile;
            // outfile.open("test.txt", std::ios_base::app);
            // if (outfile.is_open())
            // {
            //     outfile << "Start:" << j << " " << i << std::endl;
            //     outfile << "index1:" << MAX(0, i - 1) << " " << MIN(i + 1, 6) << std::endl;
            //     outfile << "index2:" << MAX(0, j - 1) << " " << MIN(j + 1, 6) << std::endl;
            //     outfile << "Mines" << cell[i * 7 + j].mines_around << std::endl;
            // }
            // outfile.close();
            // if (!cell[i * 7 + j].has_mine)
            // {
            //
            // }
        }
    }
}

void MineSweeper::show_mines()
{
    for (int i = 0; i < 49; i++)
    {
        if (cell[i].has_mine)
        {
            cell[i].set_image_from_icon_name("mine");
        }
    }
}

void MineSweeper::game_lost(int explode_index){
    for (int i = 0; i < 49; i++)
    {
        if (cell[i].has_mine && i != explode_index)
        {
            cell[i].set_image_from_icon_name("mine");
        }
    }
}

bool MineSweeper::timer_func()
{
    // Set timer
    char tmp[50];
    timer_count++;
    sprintf(tmp, "Time:%d", timer_count);
    status_label.set_label(tmp);
    return true;
}

void MineSweeper::cell_clicked(MineCell *cell1)
{
    cell1->set_relief(Gtk::RELIEF_NONE);
    if (!game_ended && !cell1->cleared)
    {
        //
        // If get mine, the game will end now
        if (cell1->has_mine)
        {
            // Set game to stop
            winned = false;
            cell1->cleared = true;
            cell1->set_image_from_icon_name("exploded");
            game_lost(cell1->y * 7 + cell1->x);
            status_label.set_label("You lost!");
            game_ended = true;
            mytimer.disconnect();
        }
        else
        {
            check_mines(cell1->x, cell1->y);
        }
    }
}

void MineSweeper::check_mines(int pos_x, int pos_y)
{
    if (pos_x >= 0 && pos_x <= 6 &&
        pos_y >= 0 && pos_y <= 6)
    {
        if (!cell[pos_y * 7 + pos_x].has_mine &&
            !cell[pos_y * 7 + pos_x].cleared)
        {
            mines_clear++;
            // std::cout << mines_clear << std::endl;
            // std::cout << pos_y << " " << pos_x << std::endl;
            if (cell[pos_y * 7 + pos_x].mines_around == 0)
            {
                // cell->set_label(" ");
                cell[pos_y * 7 + pos_x].set_image_from_icon_name("");
            }
            else
            {
                char *label = g_strdup_printf("%dmines", cell[pos_y * 7 + pos_x].mines_around);
                // status_label.set_label(label);
                cell[pos_y * 7 + pos_x].set_image_from_icon_name(label);
                g_free(label);
            }
            cell[pos_y * 7 + pos_x].set_relief(Gtk::RELIEF_NONE);
            cell[pos_y * 7 + pos_x].cleared = true;
            if (cell[pos_y * 7 + pos_x].mines_around == 0)
            {
                check_mines(pos_y - 1, pos_x - 1);
                check_mines(pos_y + 1, pos_x + 1);
                check_mines(pos_y - 1, pos_x + 1);
                check_mines(pos_y + 1, pos_x - 1);
                check_mines(pos_y, pos_x - 1);
                check_mines(pos_y, pos_x + 1);
                check_mines(pos_y + 1, pos_x);
                check_mines(pos_y - 1, pos_x);
            }
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
