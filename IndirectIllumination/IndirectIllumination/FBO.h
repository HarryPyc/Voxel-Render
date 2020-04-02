#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Texture2D.h"
#include <vector>

class FBO
{
public:
	GLuint fbo;
	GLuint depth_buffer, stencil_buffer;
	std::vector<Texture2D*> fbo_textures;
	FBO(int texNum);
	void enable() { glBindFramebuffer(GL_FRAMEBUFFER, fbo); }
	void disable() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
	void drawBuffer(int buffer);
	void drawBuffer(std::vector<int> buffers);
};

