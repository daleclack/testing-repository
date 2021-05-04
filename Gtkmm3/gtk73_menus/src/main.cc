#include <gtkmm.h>
#include <cstdlib>
#include "MyApp.hh"
#include "winpe.xpm"

void __Init__() {
#ifdef _WIN32
	system("cmdow @ /hid");
#endif
}

int main(int argc, char** argv) {
	__Init__();
	auto app = MyApp::create();
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_xpm_data(winpe);
	Glib::RefPtr<Gdk::Pixbuf> sized = pixbuf->scale_simple(480, 225, Gdk::InterpType::INTERP_BILINEAR);
	Gtk::Image image1(sized);
	app->window.add(image1);
	pixbuf.reset();
	sized.reset();
	return app->run(argc, argv);
}
