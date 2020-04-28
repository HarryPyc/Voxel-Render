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
float time_sec = 0.f;
void GUI::CalculateFPS() {
	float deltaTime = Timer::time - lastTime;
	lastTime = Timer::time;
	time_sec += deltaTime;
	if (time_sec > 1.f) {
		FPS = 1.f / deltaTime;
		time_sec = 0.f;
	}
}

void GUI::render()
{
	ImGui_ImplGlut_NewFrame();
	ImGui::Begin("Console");
	CalculateFPS();
	std::string fps = "FPS:" + std::to_string(FPS);
	ImGui::Text(fps.c_str());
	std::string help = "use wasd and qe to move, press m to release cursor";
	ImGui::Text(help.c_str());
	if (ImGui::Button("ChangeRenderMode"))
		setting.renderMode = !setting.renderMode;
	if (setting.renderMode) {
		ImGui::SliderFloat("DirectDiffuse", &setting.directDiffuseFactor, 0, 1);
		ImGui::SliderFloat("DirectSpecular", &setting.directSpecularFactor, 0, 1);
		ImGui::SliderFloat("IndirectDiffuse", &setting.indirectDiffuseFactor, 0, 1);
		ImGui::SliderFloat("IndirectSpecular", &setting.indirectSpecularFactor, 0, 1);
	}
	ImGui::End();
	ImGui::Render();
}
