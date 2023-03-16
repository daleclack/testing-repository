#include "MyPrefs.hh"

MyPrefs::MyPrefs(){
    // Set default size
    set_default_size(800, 450);
    
    // Create builder
    ref_builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/prefs_stack.ui");

    // Initalize title widget
    // Add stack switcher to the titlebar
    stack_switcher = ref_builder->get_widget<Gtk::StackSwitcher>("stack_switch");
    header.set_title_widget(*stack_switcher);
    header.set_decoration_layout("close:menu");
    header.set_show_title_buttons();
    set_titlebar(header);

    // Get Widgets
    main_stack = ref_builder->get_widget<Gtk::Stack>("main_stack");
    stack_box = ref_builder->get_widget<Gtk::Box>("stack_box");
    stack_box->set_halign(Gtk::Align::FILL);
    stack_box->set_valign(Gtk::Align::FILL);

    set_child(*stack_box);
}
