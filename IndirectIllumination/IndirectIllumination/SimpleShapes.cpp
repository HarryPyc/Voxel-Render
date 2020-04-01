#include "SimpleShapes.h"

SimpleShapes* SimpleShapes::Quad()
{
	SimpleShapes* quad = new SimpleShapes();
	quad->N = 4;
	quad->vertices.push_back(Vertex(glm::vec3(-0.5,  0.5, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0)));
	quad->vertices.push_back(Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec3(0, 0, 1), glm::vec2(1, 0)));
	quad->vertices.push_back(Vertex(glm::vec3( 0.5,  0.5, 0), glm::vec3(0, 0, 1), glm::vec2(0, 1)));
	quad->vertices.push_back(Vertex(glm::vec3( 0.5, -0.5, 0), glm::vec3(0, 0, 1), glm::vec2(1, 1)));

	quad->indices.push_back(0);
	quad->indices.push_back(1);
	quad->indices.push_back(2);
	quad->indices.push_back(3);

	quad->create_vao();
	return quad;
}

void SimpleShapes::create_vbo()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, N * 8 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	
}

void SimpleShapes::create_ebo()
{
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, N * sizeof(int), &indices[0], GL_STATIC_DRAW);
}

void SimpleShapes::create_vao()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	create_vbo();
	create_ebo();
	const int pos_loc = 0;
	const int normal_loc = 1;
	const int texcoord_loc = 2;
	glEnableVertexArrayAttrib(vao, pos_loc);
	glVertexAttribPointer(pos_loc, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(0));
	glEnableVertexArrayAttrib(vao, normal_loc);
	glVertexAttribPointer(normal_loc, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexArrayAttrib(vao, texcoord_loc);
	glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6*sizeof(float)));

}