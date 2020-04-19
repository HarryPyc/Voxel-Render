#pragma once
#include <string>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <vector>
class Texture3D
{
public:
	GLuint texture_id;
	std::string texture_name;
	Texture3D(const std::string name, int size, GLenum magFilter = GL_NEAREST, GLenum minFilter = GL_NEAREST,
		GLint internalFormat = GL_RGBA, GLint type = GL_FLOAT, GLint wrap = GL_REPEAT);
	Texture3D() {};

	void activate(GLuint program, GLuint textureLoc);
	void clear(glm::vec4 color = glm::vec4(0));
private:
	int width, height, depth;
};
