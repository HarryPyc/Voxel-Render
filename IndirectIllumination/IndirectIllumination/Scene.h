#pragma once
#include "Mesh.h"
#include "Camera.h"

#include <vector>
class Scene
{
public:
	Camera* cam;

	std::vector<Mesh*> meshes;
	
	void addMesh(Mesh* mesh);
	void render(GLuint program);
	void init();
	Scene() { init(); }
};

