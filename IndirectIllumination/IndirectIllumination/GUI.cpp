#include "GUI.h"

GUI::GUI() {
	init();
}
GUI::~GUI() {

}
float lastTime;
void GUI::init()
{
	ImGui_ImplGlut_Init();
	lastTime = Timer::time;
}

int CalculateFPS() {
	float deltaTime = Timer::time - lastTime;
	int fps = 1.f / deltaTime;
	lastTime = Timer::time;
	return fps;
}
void GUI::render()
{
	ImGui_ImplGlut_NewFrame();
	ImGui::Begin("Console");
	//ImGui::Image((void*)test_tex, ImVec2(256, 256));
	std::string fps = "FPS:" + std::to_string(CalculateFPS());
	ImGui::Text(fps.c_str());
	ImGui::End();
	ImGui::Render();
}
