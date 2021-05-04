#pragma once

#include <gtkmm.h>

class MyApp
	:public Gtk::Application
{
public:

	static Glib::RefPtr<MyApp> create();

protected:

	void on_activate() override;

private:

	Glib::RefPtr<Gtk::Builder> m_builder;
	Gtk::Window* window;
	Glib::RefPtr<Glib::Object> object;
	Glib::RefPtr<Gtk::Adjustment> main_value;
	Gtk::Scale* scale1;
	Gtk::Scale* scale2;
	Gtk::ComboBox* combo_pos;
	Gtk::Scale* digit_scale;
	Gtk::Scale* size_scale;
	Gtk::CheckButton* btn_check;
	Gtk::Button* btn_exit;

	void btncheck_clicked();
	void combopos_changed();
	void digit_changed();
	void size_changed();
	void btnexit_clicked();

};
