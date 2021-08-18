#pragma once

#include <gtkmm.h>
#include "../cfgfile2/cfgfile.hh"

class SetDialog : public Gtk::Dialog{
public:
    SetDialog(Gtk::Window & parent);
    void set_config(conf_map * src_config,Gtk::Image * src_image);
protected:
    void on_response(int response_id) override;
private:
    //Child widgets
    Gtk::Box vbox,hbox;
    Gtk::Button btnback;
    Gtk::Entry entry_back;
    Gtk::Image * img_back;

    //File Chooser Dialog
    Glib::RefPtr<Gtk::FileChooserNative> dialog;

    //File Config
    std::fstream outfile;
    conf_map *configs1;

    //Signal Handlers
    void btnload_clicked();
    void btnback_clicked();
    void dialog_reponse(int response_id);    
};
