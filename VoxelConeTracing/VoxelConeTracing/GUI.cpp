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
	std::string fps = "FPS:" + std::to_string(CalculateFPS());
	ImGui::Text(fps.c_str());
	std::string help = "use wasd and qe to move, press m to release cursor";
	ImGui::Text(help.c_str());
	ImGui::End();
	ImGui::Render();
}
