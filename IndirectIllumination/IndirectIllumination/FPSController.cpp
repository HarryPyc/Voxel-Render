#include "FPSController.h"

FPSController::FPSController(Camera* camera, int w, int h)
{
    cam = camera;
	win_w = w;
	win_h = h;
	mouseX = w / 2;
	mouseY = h / 2;
	init();
}

FPSController::~FPSController()
{
}

void FPSController::init() {
	SetCursorPos(mouseX, mouseY);
	glutSetCursor(GLUT_CURSOR_NONE);
}
void FPSController::update() {
	if(!useCursor)
		glutSetCursor(GLUT_CURSOR_NONE);
	Move();
}
void FPSController::Move()
{
	cam->pos += (hor*right() + ver*cam->dir + gravity*cam->up) * step;
}
void FPSController::OnMouseMove(int x, int y)
{
	x = x * mouseSensitivity;
	y = y * mouseSensitivity;
	yaw += x;
	pitch += y;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::mat4 R = glm::rotate(glm::radians(yaw), yAxis) * glm::rotate(glm::radians(pitch), xAxis);
	glm::vec4 t = R * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	cam->dir = normalize(glm::vec3(t));

}

void FPSController::keyboard(unsigned char key, int x, int y)
{
    ImGui_ImplGlut_KeyCallback(key);
    switch (key)
    {
	case 'w':
		ver = 1.0f;
		break;
	case 's':
		ver = -1.0f;
		break;
	case 'a':
		hor = -1.0f;
		break;
	case 'd':
		hor = 1.0f;
		break;
	case 'e':
		gravity = 1.0f;
		break;
	case 'q':
		gravity = -1.0f;
		break;
	case 'm':
		useCursor = !useCursor;
		SetCursorPos(mouseX, mouseY);
		break;
	default:
		break;
    }
}

void FPSController::keyboard_up(unsigned char key, int x, int y)
{
    ImGui_ImplGlut_KeyUpCallback(key);
	switch (key)
	{
	case 'w':
		ver = 0.0f;
		break;
	case 's':
		ver = 0.0f;
		break;
	case 'a':
		hor = 0.0f;
		break;
	case 'd':
		hor = 0.0f;
		break;
	case 'e':
		gravity = 0.0f;
		break;
	case 'q':
		gravity = 0.0f;
		break;
	default:
		break;
	}
}

void FPSController::special_up(int key, int x, int y)
{
    ImGui_ImplGlut_SpecialUpCallback(key);
}

void FPSController::passive(int x, int y)
{
    ImGui_ImplGlut_PassiveMouseMotionCallback(x, y);
	if (!useCursor) {
		glutWarpPointer(win_w / 2, win_h / 2);
		mouseX = win_w / 2;
		mouseY = win_h / 2;
		OnMouseMove(mouseX - x, mouseY - y);
	}
}

void FPSController::special(int key, int x, int y)
{
    ImGui_ImplGlut_SpecialCallback(key);
}

void FPSController::motion(int x, int y)
{
    ImGui_ImplGlut_MouseMotionCallback(x, y);

}

void FPSController::mouse(int button, int state, int x, int y)
{
    ImGui_ImplGlut_MouseButtonCallback(button, state);
}