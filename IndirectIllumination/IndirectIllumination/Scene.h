#pragma once
#include "Mesh.h"
#include "Camera.h"
#include "PointLight.h"
#include <vector>
class Scene
{
public:
	Camera* cam;

	std::vector<Mesh*> meshes;
	std::vector<PointLight*> lights;
	void addMesh(Mesh* mesh);
	void addLight(PointLight* light);

	void render(GLuint program);
	void init(GLuint program);
	void uploadLight(GLuint program);
	Scene() {}

};

