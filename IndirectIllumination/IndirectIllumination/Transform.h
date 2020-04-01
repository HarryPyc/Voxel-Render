#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
public:
	Transform(glm::vec3 pos = glm::vec3(0), glm::vec3 s = glm::vec3(1));
	glm::mat4 R, T, S, M;
	void Translate(glm::vec3 trans);
	void Rotate(float angle, glm::vec3 axis);
	void Scale(glm::vec3 s);
	void UpdateTransformMatrix();
};

