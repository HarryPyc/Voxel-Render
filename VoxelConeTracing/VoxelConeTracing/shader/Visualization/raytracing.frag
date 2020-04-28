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
uniform sampler3D albedoVoxel; 
uniform sampler3D normalVoxel;
uniform vec3 camPos; 

in vec2 tex_coord; 
out vec4 fragcolor;

// get 3D texture coordinate.
vec3 shift(vec3 p) { return 0.5f * p + vec3(0.5f); }

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
	vec3 pos;
	for(int i = 0; i < Steps; i++) {
		const vec3 currentPoint = origin + STEP_LENGTH * i * dir;
		vec3 coordinate = shift(currentPoint);
		vec4 albedoSample = textureLod(albedoVoxel, coordinate, 0.f);
		vec4 normalSample = textureLod(normalVoxel, coordinate, 0.f);
		if(albedoSample.a > 0.f){
			albedo = vec3(albedoSample);
			normal = vec3(normalSample);
			pos = currentPoint;
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