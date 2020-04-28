#version 450 core
#define MAX_LIGHT 10
struct Material {
	vec3 diffuseColor;
	float diffuseReflectivity;
	vec3 specularColor;
	float specularReflectivity;
	float emissivity;
	float transparency;
	float shiness;
};
struct PointLight{
	vec3 pos;
	vec3 color;
};

uniform PointLight pointLights[MAX_LIGHT];
uniform Material material;

layout(binding = 1, rgba8) uniform image3D albedoVoxel;
layout(binding = 0, rgba16f) uniform image3D normalVoxel;

in vec3 Pos;
in vec3 Normal;
in vec2 Tex_coord;

vec3 PhongLightingDiffuse(PointLight light);
bool isInsideCube(const vec3 p, float e) { return abs(p.x) < 1 + e && abs(p.y) < 1 + e && abs(p.z) < 1 + e; }
vec3 shift(vec3 p){ return 0.5*p + vec3(0.5); }
void main(void)
{   
	if(!isInsideCube(Pos, 0)) discard;

	
	//store color to voxels
	vec3 voxelPos = shift(Pos);
	ivec3 dim = imageSize(albedoVoxel);
	//float alpha = pow(1 - material.transparency, 4); 
	vec3 fragcolor = vec3(0);
	for(int i = 0; i<pointLights.length();i++){
		fragcolor += PhongLightingDiffuse(pointLights[i]);
	}

	ivec3 coord = ivec3(dim * voxelPos);
	//store diffuse color
	vec4 res = vec4(fragcolor, 1.0);
    imageStore(albedoVoxel, coord, res);
	//store normal
//	vec4 _n = imageLoad(normalVoxel, coord);
//	vec3 n_res = normalize(vec3(_n)+Normal);
	imageStore(normalVoxel, coord, vec4(Normal,1.f));
}

float attenuation(float d){ return 1.f/(1.f+0.1f*d+0.1f*d*d); }
vec3 PhongLightingDiffuse(PointLight light){
	vec3 l = light.pos - Pos;
	float dist = length(l);
	l = normalize(l);
	float att = attenuation(dist);
	vec3 lightColor = att*material.diffuseColor*material.diffuseReflectivity*(max(0,dot(Normal,l)));
	return lightColor*light.color;
}


















