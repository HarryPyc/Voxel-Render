#include "PointLight.h"

PointLight::PointLight(glm::vec3 _pos, glm::vec3 _color)
{
	pos = _pos;
	color = _color;
}

void PointLight::upload(GLuint program, GLuint index)
{
	glUniform3fv(glGetUniformLocation(program, ("pointLights[" + std::to_string(index) + "].pos").c_str()), 1, &pos[0]);
	glUniform3fv(glGetUniformLocation(program, ("pointLights[" + std::to_string(index) + "].color").c_str()), 1, &color[0]);
}
