#pragma once
#include <LoadMesh.h>
#include "Transform.h"
#include "Material.h"
#include "Texture2D.h"
enum MeshMode{
	simple, complex,
};
class Mesh
{
public:
	GLuint vao;
	Mesh();
	Mesh(const std::string name, glm::vec3 pos = glm::vec3(0), 
		Material* mat = Material::White(), 
		Texture2D* tex = Texture2D::Default());
	~Mesh();

	MeshData data;
	MeshMode mode;
	Transform* transform;
	Material* material;
	Texture2D* texture;
	void uploadTransformMatrix(GLuint program);
	void render();
};

