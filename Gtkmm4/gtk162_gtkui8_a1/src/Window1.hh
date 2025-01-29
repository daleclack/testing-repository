#pragma once

#include <gtkmm.h>

class Window1 : public Gtk::ApplicationWindow
{
public:
    Window1();
    virtual ~Window1();

protected:
    // Override the "destroy" signal
    bool on_close_request() override;

private:
    // Child widgets

    // Signal Handlers
};