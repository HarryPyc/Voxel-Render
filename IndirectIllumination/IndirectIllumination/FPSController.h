#pragma once
#include <imgui_impl_glut.h>
class FPSController
{
public:
	FPSController();
	~FPSController();

	void keyboard(unsigned char key, int x, int y);
	void keyboard_up(unsigned char key, int x, int y);
	void special_up(int key, int x, int y);
	void passive(int x, int y);
	void special(int key, int x, int y);
	void motion(int x, int y);
	void mouse(int button, int state, int x, int y);
};

