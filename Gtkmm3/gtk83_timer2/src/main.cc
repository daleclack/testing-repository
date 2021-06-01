#include "MyApp.hh"

int main(int argc,char **argv){
    auto app=MyApp::create();
    return app->run(argc,argv);
}
