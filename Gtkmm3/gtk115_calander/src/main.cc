#include <gtkmm.h>

class MyWin : public Gtk::Window{
    public:
        MyWin(){
            //Initalize Window
            set_icon_name("org.gtk.daleclack");
            set_default_size(400,300);
            
            //Add a Calander
            add(calander);
            show_all_children();
        }
    private:
        Gtk::Calendar calander;
};

int main(int argc,char ** argv){
    auto app = Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    MyWin window;
    app->run(window);
}
