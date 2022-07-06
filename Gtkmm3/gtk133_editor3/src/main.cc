#include "TextEditor.hh"

int main(int argc,char **argv){
    auto app = Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    auto textwin = TextEditor::create();
    return app->run(*textwin);
}