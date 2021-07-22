#include <gtkmm.h>

class MyWin : public Gtk::Window{
    //Child Widgets
    Gtk::DrawingArea draw_area;
    Gtk::ColorButton color_btn;
    Gtk::Label main_label;
    Gtk::Box main_box,btn_box;

    //Color Setting
    Gdk::RGBA m_color;
    Cairo::RefPtr<Cairo::ImageSurface> surface;

    //Gesture to draw
    Glib::RefPtr<Gtk::GestureMultiPress> gesture;
    Glib::RefPtr<Gtk::GestureDrag> drag;
    double start_x,start_y;

    //Signal Handlers
    bool draw_event(const Cairo::RefPtr<Cairo::Context> &context){
        //Show context
        context->set_source(surface,0,0);
        context->paint();
        return true;
    }

    void draw_brush(double x,double y){
        //Create Draw Brush
        auto cr=Cairo::Context::create(surface);
        cr->arc(x, y, 3, 0, 2 * G_PI);

        //Set Color
        cr->set_source_rgba(m_color.get_red(),m_color.get_green(),
                            m_color.get_blue(),m_color.get_alpha());

        //Fill Color and Delete the brush
        cr->fill();
        cr.clear();

        draw_area.queue_draw();
    }

    void button_press(int n_press, double x, double y){
        if(surface){
           //Clear the content in draw area
            auto cr=Cairo::Context::create(surface);
            cr->set_source_rgb(1,1,1);
            cr->paint();
            cr.clear();
            draw_area.queue_draw();
        }
        
    }

    void drag_begin(double x,double y){
        //The Begin
        start_x=x;start_y=y;
        draw_brush(x,y);
    }

    void drag_progress(double x,double y){
        //Progress and end
        draw_brush(x+start_x,y+start_y);
    }

    void color_set(){
        m_color=color_btn.get_rgba();
    }
public:
    MyWin()
    :main_label("Select a color"),
    main_box(Gtk::ORIENTATION_HORIZONTAL,5),
    btn_box(Gtk::ORIENTATION_VERTICAL,5)
    {
        //Ininalize window
        set_icon_name("org.gtk.daleclack");
        set_default_size(640,480);

        //Color set panel
        btn_box.pack_start(main_label,Gtk::PACK_SHRINK);
        btn_box.pack_start(color_btn,Gtk::PACK_SHRINK);
        btn_box.set_halign(Gtk::ALIGN_CENTER);
        btn_box.set_valign(Gtk::ALIGN_CENTER);

        //Add Gesture
        gesture=Gtk::GestureMultiPress::create(draw_area);
        gesture->set_button(GDK_BUTTON_SECONDARY);
        gesture->signal_pressed().connect(sigc::mem_fun(*this,&MyWin::button_press));

        drag=Gtk::GestureDrag::create(draw_area);
        drag->set_button(GDK_BUTTON_PRIMARY);
        drag->signal_drag_begin().connect(sigc::mem_fun(*this,&MyWin::drag_begin));
        drag->signal_drag_update().connect(sigc::mem_fun(*this,&MyWin::drag_progress));
        drag->signal_drag_end().connect(sigc::mem_fun(*this,&MyWin::drag_progress));

        //Create a Surface
        surface=Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32,600,480);

        //Set Default Color
        m_color.set_blue(0);
        m_color.set_green(0);
        m_color.set_red(0);
        m_color.set_alpha(1);
        color_btn.set_rgba(m_color);
        color_btn.signal_color_set().connect(sigc::mem_fun(*this,&MyWin::color_set));


        //Initalize main widget    
        draw_area.set_size_request(600,480);
        draw_area.signal_draw().connect(sigc::mem_fun(*this,&MyWin::draw_event));
        main_box.pack_start(draw_area);
        main_box.pack_start(btn_box,Gtk::PACK_SHRINK);
        main_box.set_border_width(10);
        add(main_box);
        show_all_children();
    }
};

int main(int argc,char **argv){
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    MyWin window;
    return app->run(window);
}
