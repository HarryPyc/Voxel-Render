#version 450 core

struct Material {
	vec3 diffuseColor;
	float diffuseReflectivity;
	vec3 specularColor;
	float specularReflectivity;
	float emissivity;
	float transparency;
	float shiness;
};

uniform Material material;

layout(binding = 1, rgba8) uniform image3D albedoVoxel;
layout(binding = 0, rgba16f) uniform image3D normalVoxel;

in vec3 Pos;
in vec3 Normal;
in vec2 Tex_coord;

bool isInsideCube(const vec3 p, float e) { return abs(p.x) < 1 + e && abs(p.y) < 1 + e && abs(p.z) < 1 + e; }
vec3 shift(vec3 p){ return 0.5*p + vec3(0.5); }
void main(void)
{   
	if(!isInsideCube(Pos, 0)) discard;

	
	//store color to voxels
	vec3 voxelPos = shift(Pos);
	ivec3 dim = imageSize(albedoVoxel);
	float alpha = pow(1 - material.transparency, 4); 
	vec4 res = vec4(material.diffuseColor, 1.0);
    imageStore(albedoVoxel, ivec3(dim * voxelPos), res);
	imageStore(normalVoxel, ivec3(dim * voxelPos), vec4(Normal,0.f));
}




















