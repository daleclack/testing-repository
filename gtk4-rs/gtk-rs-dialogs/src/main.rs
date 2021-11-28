use gtk::{self,
    prelude::*,glib::clone,
    gdk_pixbuf};

use std::rc::Rc;

fn main() {
    //Create a new application
    let app = gtk::Application::builder()
              .application_id("org.gtk.daleclack")
              .build();
    
    //Connect the signal
    app.connect_activate(build_ui);

    //Start the application
    app.run();
}

fn build_ui(app: &gtk::Application){
    let window = Rc::new(
                 gtk::ApplicationWindow::builder()
                 .application(app)
                 .title("gtk-rs background test")
                 .icon_name("org.gtk.daleclack")
                 .build()
    );
    
    window.set_default_size(800,450);

    let button = gtk::Button::builder()
                 .label("Dialog")
                 .halign(gtk::Align::Center)
                 .valign(gtk::Align::Center)
                 .build();

    // Connect callback
    button.connect_clicked(clone!(@strong window =>
        move|_|{
            gtk::glib::MainContext::default().spawn_local(dialog(Rc::clone(&window)));
        }
    ));

    //Create overlay and add a button
    let overlay = gtk::Overlay::new();
    overlay.add_overlay(&button);

    //Create a background
    let background = gtk::Picture::new();
    overlay.set_child(Some(&background));

    window.set_child(Some(&overlay));

    window.present();
}

async fn dialog<W: IsA<gtk::Window>>(window: Rc<W>){
    //Create a file dialog
    let file_dialog = gtk::FileChooserDialog::builder()
                      .transient_for(&*window)
                      .use_header_bar(1)
                      .build();

    //Add Buttons
    file_dialog.add_button("OK",gtk::ResponseType::Ok);
    file_dialog.add_button("Cancel",gtk::ResponseType::Cancel);

    //Add Filters
    let file_filter = gtk::FileFilter::new();
    file_filter.set_name(Some(&"Image Files"));
    file_filter.add_mime_type("image/*");
    file_dialog.add_filter(&file_filter);

    let filter_any = gtk::FileFilter::new();
    filter_any.set_name(Some(&"Any Files"));
    filter_any.add_pattern("*");
    file_dialog.add_filter(&filter_any);

    //Link Signal
    file_dialog.connect_response(dialog_responsed);
    
    file_dialog.show();
}

fn dialog_responsed(dialog : &gtk::FileChooserDialog,response_id: gtk::ResponseType){
    if response_id == gtk::ResponseType::Ok {
        //Get FileName
        let file = dialog.file();
        let filename = file.unwrap().path().unwrap();

        //Get Background widget
        let win = dialog.transient_for().unwrap();
        let overlay = win.child().unwrap().dynamic_cast::<gtk::Overlay>().unwrap();
        let background = overlay.child().unwrap().dynamic_cast::<gtk::Picture>().unwrap();

        //Create pixbuf
        let pixbuf = gdk_pixbuf::Pixbuf::from_file(filename).unwrap();
        let sized_pixbuf = pixbuf.scale_simple(800,450,gdk_pixbuf::InterpType::Bilinear).unwrap();

        background.set_pixbuf(Some(&sized_pixbuf));
    }
    dialog.destroy();
}
