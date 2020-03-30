#include "Mesh.h"

Mesh::Mesh(){}
Mesh::~Mesh(){}

Mesh::Mesh(const std::string name, glm::vec3 pos)
{
	data = LoadMesh(name);	
	vao = data.mVao;
	mode = complex;
	transform = new Transform(pos, glm::vec3(data.mScaleFactor));
}

void Mesh::uploadTransformMatrix(GLuint program)
{
	int M_loc = glGetUniformLocation(program, "M");
	if (M_loc != -1)
	{
		glUniformMatrix4fv(M_loc, 1, false, glm::value_ptr(transform->M));
	}
}

void Mesh::render() {
	glBindVertexArray(vao);
	if (mode == complex) {

		data.DrawMesh();
	}
	else if (mode == simple) {
		/*glDrawElements(GL_TRIANGLES, )*/
	}
}