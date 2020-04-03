#pragma once
#include "Scene.h"
static const std::string mesh_name = "model/Bunny.obj";


static Scene* initMainScene(GLuint program) {
	Scene* scene = new Scene();
	Mesh* quad1 = new Mesh(SimpleShapes::Quad(2.f), glm::vec3(0,0,1), Material::White());
	quad1->transform->Rotate(180.f, glm::vec3(0, 1, 0));
	Mesh* quad2 = new Mesh(SimpleShapes::Quad(2.f), glm::vec3(0, 0, -1), Material::Red());
	Mesh* quad3 = new Mesh(SimpleShapes::Quad(2.f), glm::vec3(0, 1, 0), Material::Green());
	quad3->transform->Rotate(90.f, glm::vec3(1, 0, 0));
	Mesh* quad4 = new Mesh(SimpleShapes::Quad(2.f), glm::vec3(0, -1, 0), Material::Blue());
	quad4->transform->Rotate(-90.f, glm::vec3(1, 0, 0));
	Mesh* quad5 = new Mesh(SimpleShapes::Quad(2.f), glm::vec3(1, 0, 0), Material::Orange());
	quad5->transform->Rotate(-90.f, glm::vec3(0, 1, 0));
	Mesh* quad6 = new Mesh(SimpleShapes::Quad(2.f), glm::vec3(-1, 0, 0), Material::Pink());
	quad6->transform->Rotate(90.f, glm::vec3(0, 1, 0));
	//add Cube
	scene->addMesh(quad1); scene->addMesh(quad2); scene->addMesh(quad3);
	scene->addMesh(quad4); scene->addMesh(quad5); scene->addMesh(quad6);

	Mesh* bunny = new Mesh(mesh_name,glm::vec3(0,-0.5,0),Material::Orange());
	bunny->transform->Scale(glm::vec3(2.0));
	scene->addMesh(bunny);

	scene->addLight(new PointLight(glm::vec3(0, 0.5, 0.5)));

	scene->init(program);
	return scene;
}