#include "myapplication.h"

int main(int argc,char **argv){
    //Set Schemas dir
    g_setenv("GSETTINGS_SCHEMA_DIR",".",FALSE);

    return g_application_run(G_APPLICATION(my_application_new()),argc,argv);
}
