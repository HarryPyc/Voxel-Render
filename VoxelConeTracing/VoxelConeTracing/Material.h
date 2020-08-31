#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
namespace {
	const char* colorName = "material.color";
	const char* emissionName = "material.emission" ;
	const char* specularReflectivityName = "material.specularReflectivity";
	const char* diffuseReflectivityName = "material.diffuseReflectivity";
	const char* shinessName = "material.shiness";
}
class Material
{
public:
	glm::vec3 color;
	glm::vec3 emission;
	float diffuseReflectivity, specularReflectivity, shiness;

	Material(
		glm::vec3 _color = glm::vec3(0.75f), 
		glm::vec3 _emission = glm::vec3(0), 
		float _diffuseReflectivity = 1.0f, 
		float _specularReflectivity = 1.0f, 
		float _shiness = 5.f);

	void upload(GLuint program);

	static Material* Red() {
		return new Material(glm::vec3(1, 0, 0));
	}

	static Material* Blue() {
		return new Material(glm::vec3(0, 0, 1));
	}

	static Material* Green() {
		return new Material(glm::vec3(0, 1, 0));
	}

	static Material* White() {
		return new Material(glm::vec3(1, 1, 1));
	}
	
	static Material* Orange() {
		return new Material(glm::vec3(1, 0.5, 0));
	}

	static Material* Pink() {
		return new Material(glm::vec3(1, 0.75, 0.8));
	}
};

