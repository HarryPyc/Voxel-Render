#pragma once
#include "Graphics.h"
#include "FPSController.h"
class Application
{
public:
	const int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;
	const char* title = "Voxel Cone Tracing, Harry Pan";

	void init(int argc, char** argv);

	void run();

	Graphics* graphics;

	FPSController* controller;
	static Application& getInstance();
private:
	int window;

};

