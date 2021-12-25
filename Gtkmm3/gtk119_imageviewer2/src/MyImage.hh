#pragma once

#include <gtkmm.h>

class MyImage : public Gtk::DrawingArea{
    public:
        MyImage();
        virtual ~MyImage();
        void set_pixbuf(const Glib::RefPtr<Gdk::Pixbuf> &pixbuf);
    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
        Glib::RefPtr<Gdk::Pixbuf> image;
};
