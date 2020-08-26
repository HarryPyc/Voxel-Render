#include "Texture3D.h"

Texture3D::Texture3D(const std::string name, int size, GLenum magFilter, GLenum minFilter,
	GLint internalFormat, GLint type, GLint wrap)
{
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_3D, texture_id);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, wrap);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, magFilter);
	
	glTexStorage3D(GL_TEXTURE_3D, 7, internalFormat, size, size, size);
	//glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, size, size, size, 0, GL_RGBA, type, 0);
	
	glGenerateMipmap(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, 0);
	width = size;
	height = size;
	depth = size;
	texture_name = name;
}

void Texture3D::activate(GLuint program, GLuint textureLoc)
{
	glActiveTexture(GL_TEXTURE0+textureLoc);
	glBindTexture(GL_TEXTURE_3D, texture_id);
	int tex_loc = glGetUniformLocation(program, texture_name.c_str());
	if (tex_loc != -1)
	{
		glUniform1i(tex_loc, textureLoc); // we bound our texture to texture unit 0
			
	}
}

void Texture3D::clear(glm::vec4 color)
{
	glBindTexture(GL_TEXTURE_3D, texture_id);
	glClearTexImage(texture_id, 0, GL_RGBA, GL_FLOAT, &color);
	glBindTexture(GL_TEXTURE_3D, 0);
}
