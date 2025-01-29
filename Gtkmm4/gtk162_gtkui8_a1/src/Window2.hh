#pragma once

#include <gtkmm.h>

class Window2 : public Gtk::ApplicationWindow
{
public:
    Window2();
    ~Window2();

protected:
    // Override default signal handler:
    bool on_close_request() override;

private:
    // Child widgets

    // Signal Handlers
};