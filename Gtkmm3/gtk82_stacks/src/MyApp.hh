#include <gtkmm.h>

class MyApp : public Gtk::Application{
protected:
    MyApp();
public:
    static Glib::RefPtr<MyApp> create();
protected:
    //Override default signals
    void on_startup() override;
    void on_activate() override;
private:
    //Main Builder
    Glib::RefPtr<Gtk::Builder> ref_builder;
    //Child widgets
    Gtk::Button *btn1,*btn2;
    Gtk::AspectFrame *frame1,*frame2;
    //Signal Handlers
    void btn1_clicked();
    void btn2_clicked();
};