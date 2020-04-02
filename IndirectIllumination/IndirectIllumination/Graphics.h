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
#include "MainScene.h"
#include "FBO.h"
static const std::string vertex_shader("shader/template_vs.glsl");
static const std::string fragment_shader("shader/template_fs.glsl");

class Graphics
{
public:
	Graphics();
	~Graphics();

	GLuint shader_program;
	Scene* scene;
	GUI* gui;
	FBO* fbo;
	void init();
	
	void render();
	void reload_shader();
};

