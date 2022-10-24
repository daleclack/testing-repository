#include "MineSweeper.hh"
#include <string>
#include <iostream>

MineSweeper::MineSweeper()
    : main_box(Gtk::ORIENTATION_VERTICAL, 5),
      btn_box(Gtk::ORIENTATION_HORIZONTAL, 5),
      cell(nullptr)
{
    // Initalize Window
    header.set_title("MineSweeper");
    set_titlebar(header);
    header.set_show_close_button();
    header.set_decoration_layout("close,minimize,maximize:menu");
    header.pack_end(menu_btn);
    set_icon_name("org.gtk.daleclack");

    // Initalize Menu
    menu_builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/mine_menu.xml");
    auto object = menu_builder->get_object("mine_menu");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    popover1.bind_model(gmenu);
    menu_btn.set_popover(popover1);

    // Add Actions
    add_action("new_game", sigc::mem_fun(*this, &MineSweeper::new_game));
    add_action("scores", sigc::mem_fun(*this, &MineSweeper::show_scores));
    add_action("show_mines", sigc::mem_fun(*this, &MineSweeper::show_mines));
    add_action("quit", sigc::mem_fun(*this, &MineSweeper::hide));

    // Default setting
    reset_game();

    // Buttons
    btnstart.set_label("Start/Reset");
    btnshow.set_label("Show All");
    btnexit.set_label("Exit");
    btn_box.pack_start(btnstart, Gtk::PACK_SHRINK);
    btn_box.pack_start(btnshow, Gtk::PACK_SHRINK);
    btn_box.pack_start(btnexit, Gtk::PACK_SHRINK);
    btnstart.signal_clicked().connect(sigc::mem_fun(*this, &MineSweeper::new_game));
    btnshow.signal_clicked().connect(sigc::mem_fun(*this, &MineSweeper::show_mines));
    btnexit.signal_clicked().connect(sigc::mem_fun(*this, &MineSweeper::hide));

    // Pack widgets
    status_label.set_halign(Gtk::ALIGN_CENTER);
    btn_box.set_halign(Gtk::ALIGN_CENTER);
    mine_grid.set_halign(Gtk::ALIGN_CENTER);
    main_box.pack_start(status_label, Gtk::PACK_SHRINK);
    main_box.pack_start(mine_grid);
    main_box.pack_start(btn_box, Gtk::PACK_SHRINK);

    // Create a dialog
    input_dialog = InputBox::create();

    // Create Scores Window
    scores_win = ScoresWin::create();

    // Bind windows
    input_dialog->set_transient_for(*this);
    scores_win->set_transient_for(*this);
    input_dialog->set_scores_window(scores_win);

    // Show everything
    add(main_box);
    show_all_children();
}

MineSweeper::~MineSweeper(){
    // Delete all resources
    delete input_dialog;
    delete scores_win;
    if(cell != nullptr){
        delete[] cell;
    }
}

void MineSweeper::new_game(){
    // New game = reset game
    reset_game();
}

void MineSweeper::reset_game(int width, int height, int mines)
{
    // Clear the cells
    if(cell != nullptr){
        delete[] cell;
    }

    cell = new MineCell[width * height];
    // Reset timer
    mytimer.disconnect();
    timer_count = 0;
    mytimer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &MineSweeper::timer_func), 1000);

    mine_count = 0;
    mines_clear = 0;
    mine_grid.set_sensitive();
    // Reset all data
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // Initalize cell
            cell[i * 7 + j].set_relief(Gtk::RELIEF_HALF);
            cell[i * 7 + j].set_image_from_icon_name("", Gtk::ICON_SIZE_LARGE_TOOLBAR);
            cell[i * 7 + j].set_always_show_image();
            cell[i * 7 + j].set_size_request(40, 40);
            cell[i * 7 + j].mines_around = 0;
            cell[i * 7 + j].has_mine = false;
            cell[i * 7 + j].cleared = false;
        }
    }

    // Reset mines
    while (mine_count < mines)
    {
        int index = g_random_int_range(0, width * height);
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

    // Append buttons to grid
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // cell[i * 7 + j].set_label("?");
            cell[i * width + j].signal_clicked().connect(sigc::bind(
                sigc::mem_fun(*this, &MineSweeper::cell_clicked), &cell[i * width + j]));
            mine_grid.attach(cell[i * width + j], j, i);
            cell[i * width + j].set_relief(Gtk::RELIEF_HALF);
            cell[i * width + j].x = j;
            cell[i * width + j].y = i;
            cell[i * width + j].cleared = false;
        }
    }

    mine_grid.show_all();
}

void MineSweeper::calc_mines()
{
    // Calculate the mines around a cell
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            int index1, index2;
            // The Search cell should not over the grids
            for (index1 = MAX(0, i - 1); index1 < MIN(i + 1, 6) + 1; index1++)
            {
                for (index2 = MAX(0, j - 1); index2 < MIN(j + 1, 6) + 1; index2++)
                {
                    if ((cell[index1 * 7 + index2].has_mine))
                    {
                        cell[i * 7 + j].mines_around++;
                    }
                }
            }
        }
    }
}

void MineSweeper::show_mines()
{
    // Show all cell with a mine
    for (int i = 0; i < 49; i++)
    {
        if (cell[i].has_mine)
        {
            cell[i].set_image_from_icon_name("mine", Gtk::ICON_SIZE_LARGE_TOOLBAR);
        }
    }
}

void MineSweeper::show_scores(){
    // Show Scores Window
    input_dialog->read_scores();
}

void MineSweeper::game_lost(int explode_index){
    // When a cell with mine is clicked, show other mines
    for (int i = 0; i < 49; i++)
    {
        if (cell[i].has_mine && i != explode_index)
        {
            cell[i].set_image_from_icon_name("mine", Gtk::ICON_SIZE_LARGE_TOOLBAR);
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
            cell1->set_image_from_icon_name("exploded", Gtk::ICON_SIZE_LARGE_TOOLBAR);

            // End the game
            game_lost(cell1->y * 7 + cell1->x);
            status_label.set_label("You lost!");
            game_ended = true;
            mytimer.disconnect();
            mine_grid.set_sensitive(false);
        }
        else
        {
            // If no mines, check the cell around
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
            // Show the cell has no mines around
            if (cell[pos_y * 7 + pos_x].mines_around == 0)
            {
                cell[pos_y * 7 + pos_x].set_image_from_icon_name("", Gtk::ICON_SIZE_LARGE_TOOLBAR);
            }
            else
            {
                // Show the numbers of mines around a cell
                char *label = g_strdup_printf("%dmines", cell[pos_y * 7 + pos_x].mines_around);
                cell[pos_y * 7 + pos_x].set_image_from_icon_name(label, Gtk::ICON_SIZE_LARGE_TOOLBAR);
                g_free(label);
            }

            // make the cell without mines cleared
            cell[pos_y * 7 + pos_x].set_relief(Gtk::RELIEF_NONE);
            cell[pos_y * 7 + pos_x].cleared = true;
            
            // Check the cells around a cell that has no mines
            if (cell[pos_y * 7 + pos_x].mines_around == 0)
            {
                check_mines((pos_x - 1), (pos_y - 1));
                check_mines((pos_x + 1), (pos_y + 1));
                check_mines((pos_x - 1), (pos_y + 1));
                check_mines((pos_x + 1), (pos_y - 1));
                check_mines(pos_x, (pos_y - 1));
                check_mines(pos_x, (pos_y + 1));
                check_mines((pos_x + 1), pos_y);
                check_mines((pos_x - 1), pos_y);
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
        input_dialog->set_game_time(timer_count);
        input_dialog->show_all();
    }
}
