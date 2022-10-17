#include "InputBox.hh"

InputBox::InputBox(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade)
    : Gtk::Dialog(cobject),
      ref_builder(ref_Glade)
{
}

InputBox *InputBox::create()
{
    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/win_input.ui");

    InputBox *dialog;
    builder->get_widget_derived("dialog", dialog);
}
