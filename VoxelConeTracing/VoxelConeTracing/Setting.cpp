#include "Setting.h"

void Setting::upload(GLuint program)
{
	glUniform1f(glGetUniformLocation(program, "directDiffuseFactor"), directDiffuseFactor);
	glUniform1f(glGetUniformLocation(program, "directSpecularFactor"), directSpecularFactor);
	glUniform1f(glGetUniformLocation(program, "indirectDiffuseFactor"), indirectDiffuseFactor);
	glUniform1f(glGetUniformLocation(program, "indirectSpecularFactor"), indirectSpecularFactor);

}
