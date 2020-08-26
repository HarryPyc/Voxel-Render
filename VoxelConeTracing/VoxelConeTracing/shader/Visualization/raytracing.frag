#version 450 core
#define MAX_LIGHT 10
#define STEP_LENGTH 0.005f

struct PointLight{
	vec3 pos;
	vec3 color;
};
uniform PointLight pointLights[MAX_LIGHT];
uniform sampler2D fbo_texture0; //back texture
uniform sampler2D fbo_texture1; //front texture

layout(binding = 2, r32ui) coherent volatile uniform uimage3D albedoVoxel; 

uniform vec3 camPos; 

in vec2 tex_coord; 
out vec4 fragcolor;

// get 3D texture coordinate.
vec3 shift(vec3 p) { return 0.5f * p + vec3(0.5f); }
vec4 convRGBA8ToVec4( uint val){
	return vec4(float((val&0x000000FF)), float((val&0x0000FF00)>>8U), float((val&0x00FF0000)>>16U), float((val&0xFF000000)>>24U))/255.f;
}
uint convVec4ToRGBA8( vec4 val){
	val *= 255.f;
	return (uint(val.w)&0x000000FF)<<24U | (uint(val.z)&0x000000FF)<<16U | (uint(val.y)&0x000000FF) <<8U | ( uint(val.x)&0x000000FF);
}
bool isInsideCube(vec3 p, float e) { return abs(p.x) < 1 + e && abs(p.y) < 1 + e && abs(p.z) < 1 + e; }
vec3 PhongLightingSpecular(vec3 p, vec3 n);

void main(void) {
	// Initialize ray.
	vec3 origin = isInsideCube(camPos, 0.2f) ? camPos 
	: texture(fbo_texture1, tex_coord).xyz;
	vec3 dir = texture(fbo_texture0, tex_coord).xyz - origin;
	const uint Steps = uint(length(dir) / STEP_LENGTH);
	dir = normalize(dir);

	// Trace.
	vec3 albedo = vec3(0);
	vec3 normal = vec3(0);
	const ivec3 dim = imageSize(albedoVoxel);
	for(int i = 0; i < Steps; i++) {
		const vec3 currentPoint = origin + STEP_LENGTH * i * dir;
		ivec3 coordinate = ivec3(shift(currentPoint)*dim);
		vec4 albedoSample = convRGBA8ToVec4(imageAtomicAdd(albedoVoxel, coordinate, 0));
		
		//vec4 normalSample = textureLod(normalVoxel, coordinate, 0.f);
		if(albedoSample.a > 0.0f){
			albedo = vec3(albedoSample);
			//normal = vec3(normalSample);
			break;
		}
	} 
	
	fragcolor = vec4(albedo, 1.0);
	
}
float attenuation(float d){ return 1.f/(1.f+0.1f*d+0.1f*d*d); }
vec3 PhongLightingSpecular(vec3 p, vec3 n){
	vec3 res;
	for(int i = 0; i < pointLights.length(); i++){
		vec3 l = pointLights[i].pos - p;
		float dist = length(l);
		l = normalize(l);
		float att = attenuation(dist);
		vec3 v = normalize(camPos - p);
		vec3 r = reflect(-l, n);
		vec3 specular = pointLights[i].color * att*pow(max(0,dot(r,v)), 10.0f);
		res += specular;
	}
	return res;
}