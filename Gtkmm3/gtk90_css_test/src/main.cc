#include <gtkmm.h>

class MyWin : public Gtk::Window{
public:
    MyWin()
    :main_box(Gtk::ORIENTATION_HORIZONTAL,0)
    {
        //Initalize window
        set_title("CSS Accordion");
        set_default_size(600,300);
        set_icon_name("org.gtk.daleclack");
        //Initalize Box
        main_box.set_halign(Gtk::ALIGN_CENTER);
        main_box.set_valign(Gtk::ALIGN_CENTER);

        //Add Buttons
        btn1.set_label("This");
        main_box.pack_start(btn1);

        btn2.set_label("Is");
        main_box.pack_start(btn2);

        btn3.set_label("A");
        main_box.pack_start(btn3);

        btn4.set_label("CSS");
        main_box.pack_start(btn4);

        btn5.set_label("Accordion");
        main_box.pack_start(btn5);

        btn6.set_label(":-)");
        main_box.pack_start(btn6);

        add(main_box);

        //Apply css theme
        provider=Gtk::CssProvider::create();
        provider->load_from_resource("/css_accordion/css_accordion.css");
        main_box.forall(sigc::mem_fun(*this,&MyWin::apply_css));
        style=get_style_context();
        style->add_provider(provider,G_MAXUINT);
        
        show_all_children();
    }
private:
    //Child Widgets
    Gtk::Box main_box;
    Gtk::Button btn1,btn2,btn3,btn4,btn5,btn6;
    Glib::RefPtr<Gtk::CssProvider> provider;
    Glib::RefPtr<Gtk::StyleContext> style;
    //Apply CSS for each widget
    void apply_css(Gtk::Widget &widget){
        auto style1=widget.get_style_context();
        style1->add_provider(provider,G_MAXUINT); 
    }
};

int main(int argc,char **argv){
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    MyWin window;
    return app->run(window);
}
