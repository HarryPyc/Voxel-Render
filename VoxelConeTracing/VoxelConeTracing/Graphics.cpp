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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
    initVoxelization();
	initVoxelVisualization();
	//initVoxelConeTracing();
	scene = initMainScene();
    gui = new GUI();

    //create scene

}

void Graphics::render() {
    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!isVoxelized) {
		isVoxelized = true;
		Voxelization();
	}

	//if(gui->setting.renderMode)
	//	voxelConeTracing();
	//else
		voxelVisualization();

	gui->render();

	
    glutSwapBuffers();
	glutPostRedisplay();
}

void Graphics::initVoxelization()
{
	voxel_program = Shader::voxelizationShader()->program;
	albedoVoxel = new Texture3D("albedoVoxel", voxelSize, GL_NEAREST, GL_LINEAR_MIPMAP_LINEAR, GL_R32UI, GL_CLAMP_TO_BORDER);
	normalVoxel = new Texture3D("normalVoxel", voxelSize, GL_NEAREST, GL_LINEAR_MIPMAP_LINEAR, GL_R32UI, GL_CLAMP_TO_BORDER);
	emissionVoxel = new Texture3D("emissionVoxel", voxelSize, GL_NEAREST, GL_LINEAR_MIPMAP_LINEAR, GL_R32UI, GL_CLAMP_TO_BORDER);

	glBindImageTexture(0, albedoVoxel->texture_id, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32UI);
	glBindImageTexture(1, emissionVoxel->texture_id, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32UI);
	glBindImageTexture(2, normalVoxel->texture_id, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32UI);
}
void Graphics::Voxelization() {
	glUseProgram(voxel_program);
	
	glViewport(0, 0, voxelSize, voxelSize);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	scene->uploadLight(voxel_program);
	scene->render(voxel_program);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void Graphics::initVoxelVisualization()
{
	// Materials.
	cubepos_program = Shader::CubePosShader()->program;
	raycasting_program = Shader::RayTracingShader()->program;
	
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
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	fbo->enable();
	glViewport(0, 0, w, h);
	// Back.
	glCullFace(GL_FRONT);
	fbo->drawBuffer(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cube->render(cubepos_program);

	// Front.
	glCullFace(GL_BACK);
	fbo->drawBuffer(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cube->render(cubepos_program);

	fbo->disable();

	glUseProgram(raycasting_program);
	scene->cam->upload(raycasting_program);
	scene->uploadLight(raycasting_program);
	// Settings.
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	// Activate textures.
	fbo->fbo_textures[0]->activate(raycasting_program, 0);
	fbo->fbo_textures[1]->activate(raycasting_program, 1);

	// Render 3D texture.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	quad->render(raycasting_program);
}

void Graphics::initVoxelConeTracing()
{
	VCT_program = Shader::VCTShader()->program;
}

void Graphics::voxelConeTracing()
{
	glUseProgram(VCT_program);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gui->setting.upload(VCT_program);
	albedoVoxel->activate(VCT_program, 0);
	//normalVoxel->activate(VCT_program, 1);
	scene->uploadLight(VCT_program);
	scene->render(VCT_program);
}


