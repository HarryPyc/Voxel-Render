#include "Graphics.h"

Graphics::Graphics() {
	init();
}

Graphics::~Graphics()
{
}

void Graphics::init() {
	glewInit();
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    reload_shader();
    glUseProgram(shader_program);

    gui = new GUI();

    //create scene
    scene = initMainScene(shader_program);
}

void Graphics::render() {
    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program);

    scene->uploadLight(shader_program);
    scene->render(shader_program);

    
	gui->render();

    glutSwapBuffers();
}

void Graphics::reload_shader()
{
    GLuint new_shader = InitShader(vertex_shader.c_str(), fragment_shader.c_str());

    if (new_shader == -1) // loading failed
    {
        glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
        std::cout << "Shader Loading Failed" << std::endl;
    }
    else
    {
        glClearColor(0.35f, 0.35f, 0.35f, 0.0f);

        if (shader_program != -1)
        {
            glDeleteProgram(shader_program);
        }
        shader_program = new_shader;
        
    }
}
