#pragma once
#include <GL/glew.h>
#include <iostream>
#include <InitShader.h>

class Shader
{
public:
	GLuint program;

	Shader(std::string vertexShader, std::string fragmentShader);
	Shader(std::string vertexShader, std::string geometryShader, std::string fragmentShader);
	
	static Shader* voxelizationShader() {
		return new Shader("shader/Voxelization/voxel.vert", "shader/Voxelization/voxel.geom", "shader/Voxelization/voxel.frag");
	}
	static Shader* CubePosShader() {
		return new Shader("shader/Visualization/cube.vert", "shader/Visualization/cube.frag");
	}
	static Shader* RayTracingShader() {
		return new Shader("shader/Visualization/raytracing.vert", "shader/Visualization/raytracing.frag");
	}
	static Shader* VCTShader() {
		return new Shader("shader/VCT.vert", "shader/VCT.frag");
	}
	void reload_shader(GLuint new_shader);
};

