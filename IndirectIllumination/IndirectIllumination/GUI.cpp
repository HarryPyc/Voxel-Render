#include "GUI.h"

GUI::GUI() {
	init();
}
GUI::~GUI() {

}
void GUI::init()
{
	ImGui_ImplGlut_Init();
}

void GUI::render()
{
	ImGui_ImplGlut_NewFrame();
	ImGui::SliderFloat("View Angle", &angle, -3.141592f, 3.141592f);

	ImGui::Render();
}
