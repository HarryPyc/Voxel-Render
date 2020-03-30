#include "FPSController.h"

FPSController::FPSController()
{
}

FPSController::~FPSController()
{
}

void FPSController::keyboard(unsigned char key, int x, int y)
{
    ImGui_ImplGlut_KeyCallback(key);
    switch (key)
    {
    case 'r':
    case 'R':
        break;
    }
}

void FPSController::keyboard_up(unsigned char key, int x, int y)
{
    ImGui_ImplGlut_KeyUpCallback(key);
}

void FPSController::special_up(int key, int x, int y)
{
    ImGui_ImplGlut_SpecialUpCallback(key);
}

void FPSController::passive(int x, int y)
{
    ImGui_ImplGlut_PassiveMouseMotionCallback(x, y);
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