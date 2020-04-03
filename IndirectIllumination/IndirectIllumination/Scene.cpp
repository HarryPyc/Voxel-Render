#include "Scene.h"

void Scene::addMesh(Mesh* mesh)
{
    meshes.push_back(mesh);
}

void Scene::addLight(PointLight* light)
{
    lights.push_back(light);
}

void Scene::render(GLuint program)
{
    cam->upload(program, "PV");
    std::vector<Mesh*>::iterator it = meshes.begin();
    for (it; it < meshes.end(); it++) {
        (*it)->uploadTransformMatrix(program);
        (*it)->material->upload(program);
        (*it)->texture->activate(program, GL_TEXTURE0);
        (*it)->render();
    }
}

void Scene::init(GLuint program)
{
    cam = new Camera();
    uploadLight(program);
}

void Scene::uploadLight(GLuint program)
{
    for (int i = 0; i < lights.size(); i++) {
        lights[0]->upload(program, i);
    }
}

