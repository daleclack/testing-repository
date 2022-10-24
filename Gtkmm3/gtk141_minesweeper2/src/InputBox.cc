#include "InputBox.hh"

InputBox::InputBox(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade)
    : Gtk::Dialog(cobject),
      ref_builder(ref_Glade)
{
    // Get Widgets
    ref_builder->get_widget("entry_name", entry_name);
    ref_builder->get_widget("check_scores", check_scores);
    entry_name->signal_activate().connect(sigc::mem_fun(*this, &InputBox::entry_activated));
}

void InputBox::on_response(int response_id)
{
    // Open a file to save json data
    std::fstream outfile;
    outfile.open("scores.json", std::ios_base::out);
    if (outfile.is_open())
    {
        // Insert data to json
        std::string name = std::string((entry_name->get_text()).c_str());
        names.push_back(name);
        times.push_back(game_time);
        data["name"] = names;
        data["time"] = times;

        // Output data
        outfile << data;
    }
    outfile.close();
    if (response_id == Gtk::RESPONSE_OK)
    {
        read_scores(check_scores->get_active());
    }
    hide();
}

void InputBox::read_scores(bool show_scores_win)
{
    // If show scores checkbutton is checked, show scores window
    if (show_scores_win)
    {
        scores_win1->update_and_show();
    }
}

void InputBox::set_game_time(int time)
{
    // Try to open json file
    std::fstream jsonfile;
    jsonfile.open("scores.json", std::ios_base::in);

    // If json file opened, read the data
    if (jsonfile.is_open())
    {
        data = json::parse(jsonfile);
        std::vector<std::string> names1 = data["name"];
        std::vector<int> times1 = data["time"];
        names = names1;
        times = times1;
    }
    else
    {
        // Otherwist, create json data
        data = json::parse(R"(
            {
                "name":[" "],
                "time":[0]
            }
        )");
    }
    jsonfile.close();

    // Initalize time
    game_time = time;
}

void InputBox::entry_activated()
{
    // Default response
    response(Gtk::RESPONSE_OK);
}

void InputBox::set_scores_window(ScoresWin *win1)
{
    // Bind Scores Window
    scores_win1 = win1;
}

InputBox *InputBox::create()
{
    // Create a inputbox object
    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/win_input.ui");

    InputBox *dialog;
    builder->get_widget_derived("dialog", dialog);

    return dialog;
}
