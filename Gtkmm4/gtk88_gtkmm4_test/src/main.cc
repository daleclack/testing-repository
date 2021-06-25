#include <gtkmm.h>
#include "winpe.xpm"

class MyWindow : public Gtk::Window
{
public:
    MyWindow()
    :btn_test("Change Background")
    {
        //Initalize Window
        set_default_size(640,360);
        set_icon_name("org.gtk.daleclack");
        //Add Button
        btn_test.set_halign(Gtk::Align::CENTER);
        btn_test.set_valign(Gtk::Align::CENTER);
        btn_test.signal_clicked().connect(sigc::mem_fun(*this,&MyWindow::change_background));
        overlay.add_overlay(btn_test);
        //Add Background
        back.set_can_shrink(true);
        back.set_size_request(640,360);
        back.set_keep_aspect_ratio(false);
        //Set Default Background
        auto pixbuf=Gdk::Pixbuf::create_from_xpm_data(winpe);
        back.set_pixbuf(pixbuf);
        overlay.set_child(back);
        set_child(overlay);
        pixbuf.reset();
    }

private:
    //Child Widgets
    Gtk::Picture back;
    Gtk::Overlay overlay;
    Gtk::Button btn_test;
    Gtk::FileChooserDialog *dialog;
    //Signal Handlers
    void change_background(){
        //Initalize Dialog
        dialog=new Gtk::FileChooserDialog("Choose a Image File",
                                          Gtk::FileChooser::Action::OPEN,true);
        dialog->set_transient_for(*this);
        dialog->add_button("OK",Gtk::ResponseType::OK);
        dialog->add_button("Cancel",Gtk::ResponseType::CANCEL);
        dialog->signal_response().connect(sigc::mem_fun(*this,&MyWindow::dialog_response));
        //Add File Filters
        auto filter_image=Gtk::FileFilter::create();
        filter_image->set_name("Image Files");
        filter_image->add_mime_type("image/*");
        dialog->add_filter(filter_image);

        auto filter_any=Gtk::FileFilter::create();
        filter_any->set_name("Any Files");
        filter_any->add_pattern("*");
        dialog->add_filter(filter_any);

        dialog->show();
    }

    void dialog_response(int response_id){
        if(response_id==Gtk::ResponseType::OK){
            auto file=dialog->get_file();
            back.set_file(file);
            file.reset();
        }
        delete dialog;
    }
};

int main(int argc,char **argv){
    auto app=Gtk::Application::create("org.gtk.daleclack");
    return app->make_window_and_run<MyWindow>(argc,argv);
}
