#include <gtkmm.h>

class MyWin : public Gtk::Window{
    //Child Widgets
    Gtk::Box main_box;
    Gtk::DrawingArea draw_area;
    Gtk::ColorButton color_btn;
    Gtk::Label color_label;
    //Color Defination
    Gdk::RGBA color;
    //Signal Handlers
    bool my_draw(const Cairo::RefPtr<Cairo::Context> &cr){
        Gdk::Cairo::set_source_rgba(cr,color);
        cr->paint();
        return true;
    }
    void color_changed(){
        //Get Color
        color=color_btn.get_rgba();
    }
public:
    MyWin()
    :main_box(Gtk::ORIENTATION_VERTICAL,5),
    color_label("Press Here to Change Color")
    {
        //Initalize Window
        set_default_size(260,300);
        set_icon_name("org.gtk.daleclack");

        //Add widgets
        draw_area.set_size_request(200,200);
        main_box.pack_start(draw_area,Gtk::PACK_SHRINK);
        main_box.pack_start(color_label,Gtk::PACK_SHRINK);
        main_box.pack_start(color_btn,Gtk::PACK_SHRINK);
        main_box.set_halign(Gtk::ALIGN_CENTER);
        main_box.set_valign(Gtk::ALIGN_CENTER);

        //Signals
        color_btn.signal_color_set().connect(sigc::mem_fun(*this,&MyWin::color_changed));
        draw_area.signal_draw().connect(sigc::mem_fun(*this,&MyWin::my_draw));

        //Color Setting
        color.set_alpha(1);
        color.set_blue(1);
        color.set_red(0);
        color.set_green(0);

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
