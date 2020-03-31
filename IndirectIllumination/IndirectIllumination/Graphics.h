#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <InitShader.h>
#include "GUI.h"
#include "Mesh.h"
static const std::string vertex_shader("shader/template_vs.glsl");
static const std::string fragment_shader("shader/template_fs.glsl");
static const std::string mesh_name = "model/Amago0.obj";
static const std::string fish_texture = "texture/AmagoT.bmp";
class Graphics
{
public:
	Graphics();
	~Graphics();

	std::vector<Mesh*> meshes;
	GLuint shader_program;
	GUI* gui;
	void init();
	
	void render();
	void reload_shader();
};

