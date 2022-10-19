#include "ScoresWin.hh"

ScoresWin::ScoresWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade)
    : Gtk::Window(cobject),
      ref_builder(ref_Glade)
{
    // Get Widgets
    ref_builder->get_widget("btnclose", btnclose);
    btnclose->signal_clicked().connect(sigc::mem_fun(*this, &ScoresWin::hide));
}

ScoresWin *ScoresWin::create()
{
    // Create a window
    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/scoreswin.ui");
    ScoresWin *main_win;

    builder->get_widget_derived("scores_win", main_win);

    return main_win;
}
