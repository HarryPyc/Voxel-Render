#include "Graphics.h"

Graphics::Graphics() {
	init();
}

Graphics::~Graphics()
{
}

void Graphics::init() {
	glewInit();
	RegisterCallback();
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);

	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
    initVoxelization();
	initVoxelVisualization();
	initVoxelConeTracing();
	scene = initMainScene();
    gui = new GUI();

    //create scene

}

void Graphics::render() {
    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!isVoxelized) {
		Voxelization();
		isVoxelized = true;
	}

	//voxelVisualization();
	voxelConeTracing();
	gui->render();

    glutSwapBuffers();
}

void Graphics::initVoxelization()
{
	voxel_program = Shader::voxelizationShader()->program;
	albedoVoxel = new Texture3D("albedoVoxel", voxelSize, GL_NEAREST, GL_LINEAR_MIPMAP_LINEAR, GL_RGBA, GL_FLOAT, GL_CLAMP_TO_BORDER);
	normalVoxel = new Texture3D("normalVoxel", voxelSize, GL_NEAREST, GL_NEAREST, GL_RGBA16F, GL_FLOAT, GL_REPEAT);
}
void Graphics::Voxelization() {
	glUseProgram(voxel_program);
	albedoVoxel->clear(glm::vec4(0));
	normalVoxel->clear(glm::vec4(0));
	glViewport(0, 0, voxelSize, voxelSize);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	normalVoxel->activate(voxel_program, 0);
	glBindImageTexture(0, normalVoxel->texture_id, 0, GL_TRUE, 0, GL_WRITE_ONLY, GL_RGBA16F);
	albedoVoxel->activate(voxel_program, 1);
	glBindImageTexture(1, albedoVoxel->texture_id, 0, GL_TRUE, 0, GL_WRITE_ONLY, GL_RGBA8);

	scene->uploadLight(voxel_program);
	scene->render(voxel_program);
	glGenerateMipmap(GL_TEXTURE_3D);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void Graphics::initVoxelVisualization()
{
	// Materials.
	cubepos_program = Shader::CubePosShader()->program;
	raytracing_program = Shader::RayTracingShader()->program;
	
	// FBOs.
	fbo = new FBO(2);
	// Rendering cube.
	cube = Mesh::Cube();
	cube->transform->Scale(glm::vec3(1));
	// Rendering quad.
	quad = new Mesh(SimpleShapes::Quad(2.f));
}

void Graphics::voxelVisualization()
{
	
	glUseProgram(cubepos_program);
	scene->cam->upload(cubepos_program);
	// Settings.
	glClearColor(0.35, 0.35, 0.35, 1.0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	// Back.
	glCullFace(GL_FRONT);
	fbo->enable();
	fbo->drawBuffer(0);

	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cube->render(cubepos_program);

	// Front.
	glCullFace(GL_BACK);
	fbo->drawBuffer(1);
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cube->render(cubepos_program);

	fbo->disable();
	glUseProgram(raytracing_program);
	scene->cam->upload(raytracing_program);
	scene->uploadLight(raytracing_program);
	// Settings.
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Activate textures.
	fbo->fbo_textures[0]->activate(raytracing_program, 0);
	fbo->fbo_textures[1]->activate(raytracing_program, 1);

	albedoVoxel->activate(raytracing_program, 2);
	normalVoxel->activate(raytracing_program, 3);
	// Render 3D texture.
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	quad->render(raytracing_program);
}

void Graphics::initVoxelConeTracing()
{
	VCT_program = Shader::VCTShader()->program;
}

void Graphics::voxelConeTracing()
{
	glUseProgram(VCT_program);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	albedoVoxel->activate(VCT_program, 0);
	normalVoxel->activate(VCT_program, 1);
	scene->uploadLight(VCT_program);
	scene->render(VCT_program);
}

