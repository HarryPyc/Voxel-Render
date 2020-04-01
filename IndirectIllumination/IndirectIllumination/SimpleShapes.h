#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texcoord;
	Vertex(glm::vec3 _pos, glm::vec3 _normal, glm::vec2 _texcoord) {
		pos = _pos;
		normal = _normal;
		texcoord = _texcoord;
	}
};
class SimpleShapes
{
public:
	GLuint vao;
	int N;

	static SimpleShapes* Quad();
	SimpleShapes() {};
private:
	GLuint vbo, ebo;
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	void create_vbo();
	void create_ebo();
	void create_vao();
};

