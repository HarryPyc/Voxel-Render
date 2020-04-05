#include "Mesh.h"

Mesh::Mesh(){}

Mesh::~Mesh(){}

Mesh::Mesh(SimpleShapes* _shape, glm::vec3 pos, Material* mat, Texture2D* tex)
{
	vao = _shape->vao;
	shape = _shape;
	mode = simple;
	transform = new Transform(pos);
	material = mat;
	texture = tex;
}
Mesh::Mesh(const std::string name, glm::vec3 pos, Material* mat, Texture2D* tex)
{
	data = LoadMesh(name);	
	vao = data.mVao;
	mode = complex;
	transform = new Transform(pos, glm::vec3(data.mScaleFactor));
	material = mat;
	texture = tex;
}

void Mesh::uploadTransformMatrix(GLuint program)
{
	int M_loc = glGetUniformLocation(program, "M");
	if (M_loc != -1)
	{
		glUniformMatrix4fv(M_loc, 1, false, glm::value_ptr(transform->M));
	}
}

void Mesh::render(GLuint program)
{
	uploadTransformMatrix(program);
	material->upload(program);
	//texture->activate(program, 0);
	draw();
}

void Mesh::draw() {
	glBindVertexArray(vao);
	if (mode == complex) {

		data.DrawMesh();
	}
	else if (mode == simple) {
		glDrawElements(GL_TRIANGLE_STRIP, shape->N, GL_UNSIGNED_INT, 0);
	}
}