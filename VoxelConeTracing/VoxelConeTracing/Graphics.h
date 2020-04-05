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
#include "Shader.h"
#include "Texture3D.h"
#include <DebugCallback.h>
class Graphics
{
public:
	Graphics();
	~Graphics();
	int w, h;
	GLuint shader_program;
	GLuint voxel_program, cubepos_program, raytracing_program;
	Scene* scene;
	GUI* gui;
	FBO* fbo;
	void init();
	
	void render();
private:
	GLuint voxelSize = 64;
	Texture3D *voxelTexture;
	void initVoxelization();
	void Voxelization();
	void initVoxelVisualization();
	void voxelVisualization();

	Mesh *cube, *quad;

};

