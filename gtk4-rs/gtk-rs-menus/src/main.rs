use gtk::prelude::*;
use gtk::{self,
    gio::{self}
};

fn main() {
    //Create a application
    let app = gtk::Application::builder()
                         .application_id("org.gtk.daleclack")
                         .build();

    app.connect_activate(build_ui);

    app.run();
}

fn build_ui(app:&gtk::Application){
    //Create a window
    let window = gtk::Window::builder()
                        .application(app)
                        .title("Gtk-rs menu test")
                        .icon_name("org.gtk.daleclack")
                        .build();

    window.set_default_size(800,600);

    //Create menu
    let builder = gtk::Builder::from_file("./res/menubar.xml");
    let menu:gio::MenuModel = builder.object("menubar").unwrap();

    //Create menubar
    let menubar = gtk::PopoverMenuBar::builder()
                                .menu_model(&menu)
                                .build();

    menubar.set_halign(gtk::Align::Start);
    menubar.set_valign(gtk::Align::Start);

    let vbox = gtk::Box::new(gtk::Orientation::Horizontal,5);

    vbox.append(&menubar);
    window.set_child(Some(&vbox));

    window.present();
}
