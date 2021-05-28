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
    Gtk::Button *btn1,*btn2,*btn3,*btnpg2;
    Gtk::AspectFrame *frame1,*frame2,*frame3;
    Gtk::Stack *main_stack;
    //Signal Handlers
    void btn1_clicked();
    void btn2_clicked();
    void btn3_clicked();
    void btnpg2_clicked();
};