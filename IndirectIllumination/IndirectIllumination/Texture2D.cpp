#include "Texture2D.h"

Texture2D::Texture2D(const std::string name, const std::string path)
{
	texture_id = LoadTexture(path.c_str());
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    glBindTexture(GL_TEXTURE_2D, 0);
    texture_name = name;

}

Texture2D::Texture2D(const std::string name, int w, int h)
{
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glm::vec4 color(1);
    glClearTexImage(texture_id, 0, GL_RGBA, GL_FLOAT, &color);
    glBindTexture(GL_TEXTURE_2D, 0);
    width = w;
    height = h;
    texture_name = name;
}

Texture2D::Texture2D()
{
}

void Texture2D::activate(GLuint program, GLuint textureLoc)
{
    glActiveTexture(textureLoc);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    int tex_loc = glGetUniformLocation(program, texture_name.c_str());
    if (tex_loc != -1)
    {
        glUniform1i(tex_loc, 0); // we bound our texture to texture unit 0
    }
}
