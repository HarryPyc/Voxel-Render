#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
namespace {
	const char* diffuseColorName = "material.diffuseColor";
	const char* specularColorName = "material.specularColor";
	const char* emissivityName = "material.emissivity";
	const char* transparencyName = "material.transparency";
	const char* specularReflectanceName = "material.specularReflectivity";
	const char* diffuseReflectanceName = "material.diffuseReflectivity";
}
class Material
{
public:
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float diffuseReflectivity;
	float specularReflectivity;
	float transparency;
	float emissivity;

	Material(
		glm::vec3 _diffuseColor = glm::vec3(1),
		glm::vec3 _specularColor = glm::vec3(1),
		float _diffuseReflectivity = 0.5f,
		float _specularReflectivity = 0.6f,
		float _transparency = 0.0f,
		float _emissivity = 0.0f);

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

