#include "FBO.h"
bool check_framebuffer_status();
FBO::FBO(int texNum)
{
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
    //create depth buffer
    glGenRenderbuffers(1, &depth_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
    //create fbo textures;
    for (int i = 0; i < texNum; i++) {
        fbo_textures.push_back(new Texture2D("fbo_texture" + std::to_string(i), w, h));
    }
    //Create the framebuffer object
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    for (int i = 0; i < fbo_textures.size(); i++) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, fbo_textures[i]->texture_id, 0);
    }

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);
    check_framebuffer_status();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::drawBuffer(int buffer)
{
    glDrawBuffer(GL_COLOR_ATTACHMENT0 + buffer);
}

void FBO::drawBuffer(std::vector<int> buffers)
{
    const int n = buffers.size();
    std::vector<GLenum> attachments;
    for (int i = 0; i < n; i++) {
        attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
    }
    glDrawBuffers(n, &attachments[0]);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

bool check_framebuffer_status()
{
    GLenum status;
    status = (GLenum)glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch (status) {
    case GL_FRAMEBUFFER_COMPLETE:
        return true;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        printf("Framebuffer incomplete, incomplete attachment\n");
        return false;
    case GL_FRAMEBUFFER_UNSUPPORTED:
        printf("Unsupported framebuffer format\n");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        printf("Framebuffer incomplete, missing attachment\n");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        printf("Framebuffer incomplete, missing draw buffer\n");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        printf("Framebuffer incomplete, missing read buffer\n");
        return false;
    }
    return false;
}