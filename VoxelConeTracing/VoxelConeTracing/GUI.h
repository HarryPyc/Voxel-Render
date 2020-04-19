#pragma once
#include <imgui_impl_glut.h>
#include <GL/glew.h>
#include "Timer.h"
#include <string>
class GUI
{
public:
	GUI();
	~GUI();
	void init();

	void render();
	GLuint test_tex;
private:
	int FPS;
	void CalculateFPS();
};

