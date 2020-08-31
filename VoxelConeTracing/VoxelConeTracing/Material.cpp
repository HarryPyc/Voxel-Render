#include "Material.h"

Material::Material(glm::vec3 _color, glm::vec3 _emission, float _diffuseReflectivity, float _specularReflectivity, float _shiness)
{
	color = _color;
	emission = _emission;
	diffuseReflectivity = _diffuseReflectivity;
	specularReflectivity = _specularReflectivity;
	shiness = _shiness;
}

void Material::upload(GLuint program)
{
	glUniform3fv(glGetUniformLocation(program, colorName), 1, glm::value_ptr(color));
	glUniform3fv(glGetUniformLocation(program, emissionName), 1, glm::value_ptr(emission));
	glUniform1f(glGetUniformLocation(program, diffuseReflectivityName), diffuseReflectivity);
	glUniform1f(glGetUniformLocation(program, specularReflectivityName), specularReflectivity);
	glUniform1f(glGetUniformLocation(program, shinessName), shiness);

}
