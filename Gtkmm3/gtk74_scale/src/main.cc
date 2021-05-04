#include <cstdlib>
#include "MyApp.hh"

void __App_Init() {
#ifdef _WIN32
	system("cmdow @ /hid");
#endif
}

int main(int argc, char** argv) {
	__App_Init();
	auto app = MyApp::create();
	return app->run(argc, argv);
}
