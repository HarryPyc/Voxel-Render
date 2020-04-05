#include "Camera.h"

glm::mat4 Camera::getPerspectiveMatrix(int w, int h)
{
	float aspect_ratio = float(w) / float(h);
	return glm::perspective(3.141592f / 4.f, aspect_ratio, 0.1f, 100.f);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(pos,getTarget(),up);
}

void Camera::upload(GLuint program)
{
    const int w = glutGet(GLUT_WINDOW_WIDTH);
    const int h = glutGet(GLUT_WINDOW_HEIGHT);

    glm::mat4 V = getViewMatrix();
    glm::mat4 P = getPerspectiveMatrix(w, h);
    int P_loc = glGetUniformLocation(program, "P");
    if (P_loc != -1)
    {
        glUniformMatrix4fv(P_loc, 1, false, glm::value_ptr(P));
    }
    int V_loc = glGetUniformLocation(program, "V");
    if (V_loc != -1)
    {
        glUniformMatrix4fv(V_loc, 1, false, glm::value_ptr(V));
    }
    glUniform3fv(glGetUniformLocation(program, "camPos"), 1, &pos[0]);
}

Camera::Camera(glm::vec3 _pos, glm::vec3 _target, glm::vec3 _up)
{
	pos = _pos;
	dir = glm::normalize(_target - pos);
	up = _up;
}

