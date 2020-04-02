#include "Texture3D.h"

Texture3D::Texture3D(const std::string name, int w, int h, int d)
{
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_3D, texture_id);
	glTexStorage3D(GL_TEXTURE_3D, 0, GL_RGBA8, width, height, depth);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, width, height, depth, 0, GL_RGBA, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_3D, 0);
}

void Texture3D::activate(GLuint program, GLuint textureLoc)
{
	glActiveTexture(textureLoc);
	glBindTexture(GL_TEXTURE_3D, texture_id);
	int tex_loc = glGetUniformLocation(program, texture_name.c_str());
	if (tex_loc != -1)
	{
		glUniform1i(tex_loc, 0); // we bound our texture to texture unit 0
	}
}
