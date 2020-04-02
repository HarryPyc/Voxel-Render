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
	ImGui::Begin("Console");
	ImGui::Image((void*)test_tex, ImVec2(256, 256));

	ImGui::End();
	ImGui::Render();
}
