#include "Texture3D.h"

Texture3D::Texture3D(const std::string name, int w, int h, int d)
{
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_3D, texture_id);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	const std::vector<GLfloat> buffer(4 * w * h * d, 0.0f);
	glTexStorage3D(GL_TEXTURE_3D, 7, GL_RGBA8, w, h, d);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, w, h, d, 0, GL_RGBA, GL_FLOAT, &buffer[0]);
	
	glGenerateMipmap(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, 0);
	width = w;
	height = h;
	depth = d;
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
