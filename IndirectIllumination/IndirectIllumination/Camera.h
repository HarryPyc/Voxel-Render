#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
class Camera
{
public:
	glm::vec3 pos, dir, up;

	glm::vec3 getTarget() { return pos + dir; }

	glm::mat4 getPerspectiveMatrix(int w, int h);
	glm::mat4 getViewMatrix();
	void upload(GLuint program, const std::string name);
	Camera(glm::vec3 _pos = glm::vec3(0, 0, 2), glm::vec3 _target = glm::vec3(0, 0, 0),
		glm::vec3 _up = glm::vec3(0, 1, 0));
};

