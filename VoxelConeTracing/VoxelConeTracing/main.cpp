#include "Application.h"

int main(int argc, char** argv) {
	Application::getInstance().init(argc, argv);
	Application::getInstance().run();
	return 0;
}