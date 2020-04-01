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
    reload_shader();
    gui = new GUI();
    //create scene
    scene = new Scene();
    Mesh* fish1 = new Mesh(mesh_name,glm::vec3(0),Material::Pink());
    Mesh* fish2 = new Mesh(mesh_name, glm::vec3(0.2f), Material::Orange());
    fish1->transform->Rotate(60.f, glm::vec3(0, 1, 0));
    fish2->texture = new Texture2D("tex", fish_texture);
    Mesh* quad = new Mesh(SimpleShapes::Quad());
    scene->addMesh(fish1);
    scene->addMesh(fish2);
    scene->addMesh(quad);
}

void Graphics::render() {
    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program);

    scene->cam->upload(shader_program, "PV");

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
