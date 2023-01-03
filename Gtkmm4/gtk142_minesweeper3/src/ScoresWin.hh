#pragma once

#include <gtkmm.h>
#include "jsonfile.hh"

class ScoresWin : public Gtk::Window{
    public:
        static ScoresWin *create();
        ScoresWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade);
        void update_and_show();

    private:
        Glib::RefPtr<Gtk::Builder> ref_builder;

        // Child widgets
        Gtk::Button *btnclose;
        Gtk::TreeView *tree_view;

        // TreeView data
        class ModelColumns : public Gtk::TreeModelColumnRecord{
            public:
                ModelColumns(){
                    add(player_name);
                    add(win_time);
                }
                Gtk::TreeModelColumn<std::string> player_name;
                Gtk::TreeModelColumn<int> win_time;
        };
        ModelColumns column1;

        Glib::RefPtr<Gtk::ListStore> store;

        // Sort function
        int sort_func(const Gtk::TreeModel::const_iterator &iter1, const Gtk::TreeModel::const_iterator &iter2);
};
