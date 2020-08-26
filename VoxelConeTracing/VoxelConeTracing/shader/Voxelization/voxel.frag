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

layout(binding = 0, r32ui) uniform coherent volatile uimage3D albedoVoxel;
//layout(binding = 0, r32ui) coherent volatile uniform uimage3D normalVoxel;

in vec3 Pos;
in vec3 Normal;
in vec2 Tex_coord;

vec3 PhongLightingDiffuse(PointLight light);
bool isInsideCube(const vec3 p, float e) { return abs(p.x) < 1 + e && abs(p.y) < 1 + e && abs(p.z) < 1 + e; }
vec3 shift(vec3 p){ return 0.5*p + vec3(0.5); }
vec4 convRGBA8ToVec4( uint val){
	return vec4(float((val&0x000000FF)), float((val&0x0000FF00)>>8U), float((val&0x00FF0000)>>16U), float((val&0xFF000000)>>24U))/255.f;
}
uint convVec4ToRGBA8( vec4 val){
	val *= 255.f;
	return (uint(val.w)&0x000000FF)<<24U | (uint(val.z)&0x000000FF)<<16U | (uint(val.y)&0x000000FF) <<8U | ( uint(val.x)&0x000000FF);
}
void imageAtomicRGBA8Avg( layout ( r32ui ) coherent volatile uimage3D imgUI , ivec3 coords , vec4 val) {
	uint newVal = convVec4ToRGBA8(val);
	uint prevStoredVal = 0; uint curStoredVal;
	// Loop as long as destination value gets changed by other threads
	while ( ( curStoredVal = imageAtomicCompSwap( imgUI , coords , prevStoredVal , newVal )) != prevStoredVal){
		prevStoredVal = curStoredVal;
		vec4 rval = convRGBA8ToVec4( curStoredVal);
		rval. xyz =( rval. xyz* rval.w); // Denormalize
		vec4 curValF = rval+ val; // Add new value
		curValF .xyz /=( curValF .w); // Renormalize
		newVal = convVec4ToRGBA8( curValF );
	}
}
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
	imageAtomicRGBA8Avg(albedoVoxel, coord, res);
    //uint curStoredVal = imageAtomicExchange(albedoVoxel, coord, convVec4ToRGBA8(res));
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


















