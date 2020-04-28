#pragma once
#include <GL/glew.h>

struct Setting {
	bool renderMode = true;

	float directDiffuseFactor = 0.6f;
	float directSpecularFactor = 1.0f;
	float indirectDiffuseFactor = 0.5f;
	float indirectSpecularFactor = 0.3f;

	void upload(GLuint program);
};
