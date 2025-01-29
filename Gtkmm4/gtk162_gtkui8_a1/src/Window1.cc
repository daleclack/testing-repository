#include "Window1.hh"

Window1::Window1()
{

}

bool Window1::on_close_request()
{
    g_print("The window is closing\n");
    set_visible(false);
    return true;
}

Window1::~Window1()
{
    
}