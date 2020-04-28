#pragma once
#include <GL/glew.h>

struct Setting {
	bool renderMode = true;

	float directDiffuseFactor = 0.8f;
	float directSpecularFactor = 0.8f;
	float indirectDiffuseFactor = 0.3f;
	float indirectSpecularFactor = 0.3f;

	void upload(GLuint program);
};
