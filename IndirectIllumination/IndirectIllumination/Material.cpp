#include "Material.h"

Material::Material(glm::vec3 _diffuseColor, glm::vec3 _specularColor, float _diffuseReflectivity, float _specularReflectivity, float _transparency, float _emissivity, float _shiness)
{
	diffuseColor = _diffuseColor;
	specularColor = _specularColor;
	diffuseReflectivity = _diffuseReflectivity;
	specularReflectivity = _specularReflectivity;
	transparency = _transparency;
	emissivity = _emissivity;
	shiness = _shiness;
}

void Material::upload(GLuint program)
{
	glUniform3fv(glGetUniformLocation(program, diffuseColorName), 1, glm::value_ptr(diffuseColor));
	glUniform1f(glGetUniformLocation(program, diffuseReflectanceName), diffuseReflectivity);
	glUniform3fv(glGetUniformLocation(program, specularColorName), 1, glm::value_ptr(specularColor));
	glUniform1f(glGetUniformLocation(program, specularReflectanceName), specularReflectivity);

	glUniform1f(glGetUniformLocation(program, transparencyName), transparency);
	glUniform1f(glGetUniformLocation(program, emissivityName), emissivity);
	glUniform1f(glGetUniformLocation(program, shinessName), shiness);

}
