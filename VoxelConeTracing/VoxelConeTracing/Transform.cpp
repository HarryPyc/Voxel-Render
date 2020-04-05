#include "Transform.h"
Transform::Transform(glm::vec3 pos, glm::vec3 s)
{
	T = glm::translate(pos);
	R = glm::rotate(0.f, glm::vec3(0, 0, 1));
	S = glm::scale(s);
	UpdateTransformMatrix();
}
void Transform::Translate(glm::vec3 trans) {
	T = glm::translate(trans);
	UpdateTransformMatrix();
}

void Transform::Rotate(float angle, glm::vec3 axis) {
	R = glm::rotate(glm::radians(angle), axis);
	UpdateTransformMatrix();
}

void Transform::Scale(glm::vec3 s) {
	S = glm::scale(s);
	UpdateTransformMatrix();
}

void Transform::UpdateTransformMatrix()
{
	M = T * R * S;
}
