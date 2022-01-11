#include "MyWin.hh"

MyWin *MyWin::create()
{
    MyWin *win = nullptr;

    auto builder1 = Gtk::Builder::create_from_resource("/org/gtk/daleclack/stack.ui");
    builder1->get_widget_derived("window", win);
    win->set_icon_name("org.gtk.daleclack");

    return win;
}

MyWin::MyWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder)
    : Gtk::Window(cobject),
      ref_builder(builder)
{
    //Get Widgets
    ref_builder->get_widget("btn_go",btn_go);
    ref_builder->get_widget("btn_back",btn_back);
    ref_builder->get_widget("start_grid",start_grid);
    ref_builder->get_widget("test_grid",test_grid);
    ref_builder->get_widget("main_stack",main_stack);

    //Link Signals
    btn_go->signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btngo_clicked));
    btn_back->signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnback_clicked));
}

void MyWin::btngo_clicked(){
    main_stack->set_visible_child(*test_grid);
}

void MyWin::btnback_clicked(){
    main_stack->set_visible_child(*start_grid);
}
