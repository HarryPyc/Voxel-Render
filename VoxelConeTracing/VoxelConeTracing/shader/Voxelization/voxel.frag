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
uniform vec3 camPos;
uniform Material material;
uniform PointLight pointLights[MAX_LIGHT];

layout(RGBA8) uniform image3D VoxelTexture;

in vec3 Pos;
in vec3 Normal;
in vec2 Tex_coord;

bool isInsideCube(const vec3 p, float e) { return abs(p.x) < 1 + e && abs(p.y) < 1 + e && abs(p.z) < 1 + e; }
vec3 PhongLightingModel(PointLight light);
vec3 shift(vec3 p){ return 0.5*p + vec3(0.5); }
void main(void)
{   
	if(!isInsideCube(Pos, 0)) discard;
	vec3 lightColor = material.emissivity*material.diffuseColor;
	for(int i = 0; i < pointLights.length(); i++){
		lightColor += PhongLightingModel(pointLights[i]);
	}
	
	vec4 fragcolor = vec4(lightColor,1);
	
	//store color to voxels
	vec3 voxelPos = shift(Pos);
	ivec3 dim = imageSize(VoxelTexture);
	float alpha = pow(1 - material.transparency, 4); 
	vec4 res = alpha * fragcolor;
    imageStore(VoxelTexture, ivec3(dim * voxelPos), res);
}

float attenuation(float d){ return 1.f/(1.f+0.5f*d+0.5f*d*d); }
vec3 PhongLightingModel(PointLight light){
	vec3 l = light.pos - Pos;
	float dist = length(l);
	l = normalize(l);
	float att = attenuation(dist);
	vec3 v = normalize(camPos - Pos);
	vec3 r = reflect(-l,Normal);

	vec3 lightColor = 0.3f*material.diffuseColor + att*(material.diffuseColor*material.diffuseReflectivity*max(0,dot(Normal,l))
		+ material.specularColor*material.specularReflectivity*pow(max(0,dot(r,v)),material.shiness));
	return lightColor*light.color;
}


















