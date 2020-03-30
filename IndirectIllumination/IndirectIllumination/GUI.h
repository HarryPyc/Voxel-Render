#pragma once
#include <imgui_impl_glut.h>
class GUI
{
public:
	GUI();
	~GUI();
	void init();

	void render();

	float angle = 0.f;
};

