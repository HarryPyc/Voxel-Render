#include "Shader.h"

Shader::Shader(std::string vertexShader, std::string fragmentShader)
{
    reload_shader(InitShader(vertexShader.c_str(), fragmentShader.c_str()));
}

Shader::Shader(std::string vertexShader, std::string geometryShader, std::string fragmentShader)
{
    reload_shader(InitShader(vertexShader.c_str(), geometryShader.c_str(),fragmentShader.c_str()));

}

void Shader::reload_shader(GLuint new_shader)
{
    if (new_shader == -1) // loading failed
    {
        glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
        std::cout << "Shader Loading Failed" << std::endl;
    }
    else
    {
        glClearColor(0.35f, 0.35f, 0.35f, 0.0f);

        if (program != -1)
        {
            glDeleteProgram(program);
        }
        program = new_shader;
    }
}
