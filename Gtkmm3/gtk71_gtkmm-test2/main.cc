#include <gtkmm/application.h>
#include <gtkmm/image.h>
#include <cstdlib>
#include "GtkWin.h"
#include "winpe.xpm"

void Init(void) {
	//This command is for windows only
#ifdef _WIN32
	system("cmdow @ /hid");
#endif	
}

int main(int argc, char** argv) {
	Init();
	//Start a application
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.test");
	GtkWin window;
	//Image
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_xpm_data(winpe);
	Glib::RefPtr<Gdk::Pixbuf> sized = pixbuf->scale_simple(640, 360, Gdk::InterpType::INTERP_BILINEAR);
	Gtk::Image image1(sized);
	window.overlay.add(image1);
	window.show_all();
	return app->run(window);
	pixbuf.reset();
	sized.reset();
}
