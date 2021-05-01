#pragma once

#include <gtkmm/window.h>
#include <gtkmm/overlay.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>

class GtkWin :
	public Gtk::Window
{
public:
	GtkWin();
	virtual ~GtkWin();
	Gtk::Overlay overlay;
protected:
	Gtk::Button m_button;
	void on_button_clicked();
};
