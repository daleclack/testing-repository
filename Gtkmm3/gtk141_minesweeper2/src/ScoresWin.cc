#include "ScoresWin.hh"

ScoresWin::ScoresWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade)
    : Gtk::Window(cobject),
      ref_builder(ref_Glade)
{
    // Get Widgets
    ref_builder->get_widget("btnclose", btnclose);
    ref_builder->get_widget("scores_view", tree_view);
    btnclose->signal_clicked().connect(sigc::mem_fun(*this, &ScoresWin::hide));

    // Create the list store
    store = Gtk::ListStore::create(column1);
    tree_view->set_model(store);
    tree_view->append_column("name", column1.player_name);
    tree_view->append_column("time", column1.win_time);
}

void ScoresWin::show_with_vectors(std::vector<std::string> &name_vec, std::vector<int> &time_vec){
    // Clear the store
    store->clear();

    // Append data to the store
    for(int i = 0; i < name_vec.size(); i++){
        auto row = *(store->append());
        row[column1.player_name] = name_vec[i];
        row[column1.win_time] = time_vec[i];
    }
    store->set_sort_func(column1.win_time, sigc::mem_fun(*this, &ScoresWin::sort_func));

    show_all();
}

int ScoresWin::sort_func(const Gtk::TreeModel::iterator &iter1, const Gtk::TreeModel::iterator &iter2){
    auto row1 = *iter1;
    auto row2 = *iter2;
    if(row1[column1.win_time] < row2[column1.win_time]){
        return -1;
    }
    if(row1[column1.win_time] == row2[column1.win_time]){
        return 0;
    }else{
        return 1;
    }
}

ScoresWin *ScoresWin::create()
{
    // Create a window
    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/scoreswin.ui");
    ScoresWin *main_win;

    builder->get_widget_derived("scores_win", main_win);

    return main_win;
}
