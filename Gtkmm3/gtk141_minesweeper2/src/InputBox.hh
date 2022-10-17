#pragma once

#include <gtkmm.h>
#include <vector>
#include "../json_nlohmann/json.hpp"

using json = nlohmann::json;

class InputBox : public Gtk::Dialog{
    public:
        static InputBox *create(Gtk::Window &parent);
        InputBox(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade);
        void set_game_time(int time);
    
    protected:
        void on_response(int response_id) override;
    
    private:
        int game_time;

        // Data to write to json file
        json data;
        std::vector<std::string> names;
        std::vector<int> times;

        // Builder Object
        Glib::RefPtr<Gtk::Builder> ref_builder;

        // Child widget
        Gtk::Entry *entry_name;

        // Signal Handlers
        void entry_activated();
};