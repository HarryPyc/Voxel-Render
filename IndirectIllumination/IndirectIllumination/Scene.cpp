#include "Scene.h"

void Scene::addMesh(Mesh* mesh)
{
    meshes.push_back(mesh);
}

void Scene::render(GLuint program)
{
    std::vector<Mesh*>::iterator it = meshes.begin();
    for (it; it < meshes.end(); it++) {
        (*it)->uploadTransformMatrix(program);
        (*it)->material->upload(program);
        (*it)->texture->activate(program, GL_TEXTURE0);
        (*it)->render();
    }
}

void Scene::init()
{
	cam = new Camera();
}

