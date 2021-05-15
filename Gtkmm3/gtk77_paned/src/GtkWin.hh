#include <gtkmm.h>

class MyWin : public Gtk::Window{
    public:
    MyWin();
    virtual ~MyWin();

    Gtk::Paned m_paned;
    Gtk::Frame frame1;
    Gtk::Frame frame2;
};