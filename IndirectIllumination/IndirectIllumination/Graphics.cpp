#include "Graphics.h"

Graphics::Graphics() {
	init();
	gui = new GUI();
}

Graphics::~Graphics()
{
}

void Graphics::init() {
	glewInit();
	glEnable(GL_DEPTH_TEST);
    reload_shader();
    meshes.push_back(new Mesh(mesh_name, glm::vec3(0)));
    meshes.push_back(new Mesh(mesh_name, glm::vec3(0.2f)));
    meshes[1]->transform->Rotate(60.f, glm::vec3(0, 1, 0));
}

void Graphics::render() {
    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program);

    const int w = glutGet(GLUT_WINDOW_WIDTH);
    const int h = glutGet(GLUT_WINDOW_HEIGHT);
    const float aspect_ratio = float(w) / float(h);

    
    glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 1.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(gui->angle, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 P = glm::perspective(3.141592f / 4.0f, aspect_ratio, 0.1f, 100.0f);

    int PV_loc = glGetUniformLocation(shader_program, "PV");
    if (PV_loc != -1)
    {
        glm::mat4 PV = P * V;
        glUniformMatrix4fv(PV_loc, 1, false, glm::value_ptr(PV));
    }
    std::vector<Mesh*>::iterator it = meshes.begin();
    for (it; it < meshes.end(); it++) {
        (*it)->uploadTransformMatrix(shader_program);
        (*it)->render();
    }

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
