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

Texture2D::Texture2D(const std::string name, int w, int h, GLenum magFilter, GLenum minFilter, GLint internalFormat, GLint type, GLint wrap)
{
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, GL_RGBA, type, 0);
    /*glm::vec4 color(1);
    glClearTexImage(texture_id, 0, GL_RGBA, GL_FLOAT, &color);*/
    glGenerateMipmap(GL_TEXTURE_2D);
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
    glActiveTexture(GL_TEXTURE0 + textureLoc);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    int tex_loc = glGetUniformLocation(program, texture_name.c_str());
    if (tex_loc != -1)
    {
        glUniform1i(tex_loc, textureLoc); // we bound our texture to texture unit 0
    }
}
