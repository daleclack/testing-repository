#pragma once

#include <gtkmm.h>

class MyApp : public Gtk::Application{
protected:
    MyApp();

public:
    static Glib::RefPtr<MyApp> create();
    Gtk::ApplicationWindow window;

protected:
  //Overrides of default signal handlers:
    void on_startup() override;
    void on_activate() override;

private:
    
    Glib::RefPtr<Gtk::Builder> m_refBuilder;

};