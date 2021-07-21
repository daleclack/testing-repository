#include <gtkmm.h>

class MyWin : public Gtk::Window{
    //Child Widgets
    Gtk::Box main_box;
    Gtk::DrawingArea draw_area;
    Gtk::Button color_btn;
    //Signal Handlers
    bool my_draw(const Cairo::RefPtr<Cairo::Context> &cr){
        cr->set_source_rgba(0,0,1,1);
        cr->paint();
        return false;
    }
public:
    MyWin()
    :main_box(Gtk::ORIENTATION_VERTICAL,5),
    color_btn("Change Color")
    {
        //Initalize Window
        set_default_size(260,300);
        set_icon_name("org.gtk.daleclack");

        //Add widgets
        draw_area.set_size_request(200,200);
        main_box.pack_start(draw_area,Gtk::PACK_SHRINK);
        main_box.pack_start(color_btn,Gtk::PACK_SHRINK);
        main_box.set_halign(Gtk::ALIGN_CENTER);
        main_box.set_valign(Gtk::ALIGN_CENTER);

        //Draw Event
        draw_area.signal_draw().connect(sigc::mem_fun(*this,&MyWin::my_draw));

        //Show Everything
        add(main_box);
        show_all_children();
    }
};

int main(int argc,char **argv){
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    MyWin window;
    return app->run(window);
}
