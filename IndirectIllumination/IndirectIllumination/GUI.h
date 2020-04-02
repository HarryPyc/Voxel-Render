#pragma once
#include <imgui_impl_glut.h>
#include <GL/glew.h>
class GUI
{
public:
	GUI();
	~GUI();
	void init();

	void render();
	GLuint test_tex;
};

