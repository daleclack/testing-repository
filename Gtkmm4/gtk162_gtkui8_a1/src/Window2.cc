#include "Window2.hh"

Window2::Window2()
{

}

bool Window2::on_close_request()    
{
    set_visible(false);
    return true;
}

Window2::~Window2()
{}