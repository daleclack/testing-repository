#include "InputBox.hh"
#include <fstream>

InputBox::InputBox(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade)
    : Gtk::Dialog(cobject),
      ref_builder(ref_Glade)
{
    // Get Widgets
    ref_builder->get_widget("entry_name", entry_name);
}

void InputBox::on_response(int response_id){
    if(response_id == Gtk::RESPONSE_OK){
        // Open a file to save json data
        std::fstream outfile;
        outfile.open("scores.json", std::ios_base::out);
        if(outfile.is_open()){
            // Insert data to json
            std::string name = std::string((entry_name->get_text()).c_str());
            names.push_back(name);
            times.push_back(game_time);
            data["name"] = names;
            data["time"] = times;

            // Output data
            outfile<<data;
        }
        outfile.close();
    }
    hide();
}

void InputBox::set_game_time(int time){
    // Try to open json file
    std::fstream jsonfile;
    jsonfile.open("scores.json", std::ios_base::in);
    
    // If json file opened, read the data
    if(jsonfile.is_open()){
        data = json::parse(jsonfile);
        std::vector<std::string> names1 = data["name"];
        std::vector<int> times1 = data["time"];
        names = names1;
        times = times1;
    }else{
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

InputBox *InputBox::create(Gtk::Window &parent)
{
    // Create a inputbox object
    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/win_input.ui");

    InputBox *dialog;
    builder->get_widget_derived("dialog", dialog);
    dialog->set_transient_for(parent);

    return dialog;
}
