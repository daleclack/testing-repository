#include "MyApp.hh"

Glib::RefPtr<MyApp> MyApp::create() {
	return Glib::RefPtr<MyApp>(new MyApp());
}

void MyApp::on_activate() {
	//Create a builder and get widgets
	m_builder = Gtk::Builder::create_from_resource("/gtk74/window.ui");
	//Main window
	m_builder->get_widget("window", window);
	window->set_title("Gtk (74)");
	add_window(*window);
	//Show Value Button
	m_builder->get_widget("btnshow", btn_check);
	btn_check->signal_clicked().connect(sigc::mem_fun(*this, &MyApp::btncheck_clicked));
	//Scale buttons
	m_builder->get_widget("scale1", scale1);
	m_builder->get_widget("scale2", scale2);
	//Position ComboBox
	m_builder->get_widget("combo_pos", combo_pos);
	combo_pos->signal_changed().connect(sigc::mem_fun(*this, &MyApp::combopos_changed));
	//Digit setting
	m_builder->get_widget("digit_scale", digit_scale);
	digit_scale->signal_value_changed().connect(sigc::mem_fun(*this, &MyApp::digit_changed));
	//Page size Setting
	object = m_builder->get_object("adjustment1");
	main_value = Glib::RefPtr<Gtk::Adjustment>::cast_static(object);
	m_builder->get_widget("size_scale", size_scale);
	size_scale->signal_value_changed().connect(sigc::mem_fun(*this, &MyApp::size_changed));
	//Exit Button
	m_builder->get_widget("btnexit", btn_exit);
	btn_exit->signal_clicked().connect(sigc::mem_fun(*this, &MyApp::btnexit_clicked));
	window->show_all();
}

void MyApp::btncheck_clicked() {
	bool checked;
	checked = btn_check->get_active();
	scale1->set_draw_value(checked);
	scale2->set_draw_value(checked);
}

void MyApp::combopos_changed() {
	//Change the position of scales
	int index;
	index = combo_pos->get_active_row_number();
	Gtk::PositionType pos = Gtk::PositionType::POS_TOP;
	//g_print("%d\n", index);
	switch (index) {
	case 0:
		pos = Gtk::PositionType::POS_TOP; break;
	case 1:
		pos = Gtk::PositionType::POS_BOTTOM; break;
	case 2:
		pos = Gtk::PositionType::POS_LEFT; break;
	case 3:
		pos = Gtk::PositionType::POS_RIGHT; break;
	}
	scale1->set_value_pos(pos);
	scale2->set_value_pos(pos);
}

void MyApp::digit_changed() {
	//Change Digits
	int digits;
	digits = digit_scale->get_value();
	scale1->set_digits(digits);
	scale2->set_digits(digits);
}

void MyApp::size_changed() {
	//Change Page Size
	double page_size;
	page_size = size_scale->get_value();
	//g_print("%f\n", page_size);
	main_value->set_page_size(page_size);
}

void MyApp::btnexit_clicked() {
	delete window;
}
