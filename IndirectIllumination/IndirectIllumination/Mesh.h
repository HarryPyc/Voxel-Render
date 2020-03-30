#pragma once
#include <LoadMesh.h>
#include "Transform.h"
enum MeshMode{
	simple, complex,
};
class Mesh
{
public:
	GLuint vao;
	Mesh();
	Mesh(const std::string name, glm::vec3 pos);
	~Mesh();

	MeshData data;
	MeshMode mode;
	Transform* transform;
	void uploadTransformMatrix(GLuint program);
	void render();
};

