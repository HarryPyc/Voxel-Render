#pragma once
#include <string>
#include <gl/glew.h>


class Texture3D
{
public:
	GLuint texture_id;
	std::string texture_name;
	Texture3D(const std::string name, int w, int h, int d);
	Texture3D() {};

	void activate(GLuint program, GLuint textureLoc);

private:
	int width, height, depth;
};
