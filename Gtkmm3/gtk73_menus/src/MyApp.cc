#include "MyApp.hh"
#include <iostream>

MyApp::MyApp()
: Gtk::Application ("org.gtk.daleclack"){
    Glib::set_application_name("Main Menu Example");
}

Glib::RefPtr<MyApp> MyApp::create(){
    return Glib::RefPtr<MyApp>(new MyApp());
}

void MyApp::on_startup(){
    Gtk::Application::on_startup();

    m_refBuilder = Gtk::Builder::create();

    Glib::ustring ui_info=
    "<interface>"
    "    <menu id='app-menu'>"
    "      <section>"
    "        <submenu>"
    "          <attribute name='label'>File</attribute>"
    "          <item>"
    "            <attribute name='label'>Exit Application</attribute>"
    "          </item>"
    "        </submenu>"
    "        <submenu>"
    "            <attribute name='label'>Edit</attribute>"
    "          <item>"
    "            <attribute name='label'>Copy    (Ctrl-C)</attribute>"
    "          </item>"
    "          <item>"
    "            <attribute name='label'>Paste   (Ctrl-V)</attribute>"
    "          </item>"
    "        </submenu>"
    "        <submenu>"
    "          <attribute name='label'>Help</attribute>"
    "          <item>"
    "            <attribute name='label'>About The Application</attribute>"
    "          </item>"
    "        </submenu>"
    "      </section>"
    "    </menu>"
    "</interface>";

    try
    {
        m_refBuilder->add_from_string(ui_info);
    }

    catch (const Glib::Error& ex)
    {
        std::cerr << "Building menus failed: " << ex.what();
    }

    auto object = m_refBuilder->get_object("app-menu");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);

    if (!(gmenu)) {
        g_warning("GMenu or AppMenu not found");
    }
    else
    {
        set_menubar(gmenu);
    }
}

void MyApp::on_activate(){
    add_window(window);
    window.set_default_size(480,225);
    window.set_icon_name("org.gtk.daleclack");
    window.show_all();
}
