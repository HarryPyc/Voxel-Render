#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
class PointLight
{
public:
	glm::vec3 pos;
	glm::vec3 color;

	PointLight(glm::vec3 _pos, glm::vec3 _color = glm::vec3(1));

	void upload(GLuint program, GLuint index);
};

