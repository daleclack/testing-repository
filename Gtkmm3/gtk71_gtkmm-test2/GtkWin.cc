#include "GtkWin.h"

GtkWin::GtkWin()
	:m_button("Test") {
	//Window Setting
	set_default_size(640, 360);
	set_icon_name("org.gtk.daleclack");
	set_title("Gtkmm 3 test");
	//Button
	m_button.set_halign(Gtk::Align::ALIGN_CENTER);
	m_button.set_valign(Gtk::Align::ALIGN_CENTER);
	m_button.signal_clicked().connect(sigc::mem_fun(*this, &GtkWin::on_button_clicked));
	overlay.add_overlay(m_button);
	add(overlay);
}

GtkWin::~GtkWin() {

}

void GtkWin::on_button_clicked() {
	Gtk::Dialog dialog1;
	Gtk::Label label1("Hello");
	Gtk::Box* box;
	dialog1.add_button("OK", GTK_RESPONSE_OK);
	dialog1.set_default_size(400, 200);
	dialog1.set_title("Dialog Hello");
	dialog1.set_transient_for(*this);
	box = dialog1.get_content_area();
	box->pack_start(label1);
	box->show_all();
	dialog1.run();
}
