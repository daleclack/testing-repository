#include "ColorRef.hh"

ColorButton::ColorButton(){
    set_always_show_image();
    set_image(image);
    image.signal_draw().connect(sigc::mem_fun(*this,&ColorButton::image_draw));
}

bool ColorButton::image_draw(const Cairo::RefPtr<Cairo::Context> &context){
    
}