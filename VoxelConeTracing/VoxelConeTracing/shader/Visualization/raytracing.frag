#version 450 core
#define MAX_LIGHT 10
#define STEP_LENGTH 0.005f
#define INV_STEP_LENGTH (1.0f/STEP_LENGTH)
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
vec4 PhongLighting(vec3 p, vec3 n, vec3 albedo);

void main(void) {
	// Initialize ray.
	vec3 origin = isInsideCube(camPos, 0.2f) ? camPos 
	: texture(fbo_texture1, tex_coord).xyz;
	vec3 dir = texture(fbo_texture0, tex_coord).xyz - origin;
	const uint Steps = uint(INV_STEP_LENGTH * length(dir));
	dir = normalize(dir);

	// Trace.
	vec3 albedo = vec3(0);
	vec3 normal = vec3(0);
	vec3 pos;
	for(int i = 0; i < Steps && (albedo==vec3(0.f) || normal==vec3(0.f)); i++) {
		const vec3 currentPoint = origin + STEP_LENGTH * i * dir;
		vec3 coordinate = shift(currentPoint);
		vec4 albedoSample = textureLod(albedoVoxel, coordinate, 0);
		vec4 normalSample = textureLod(normalVoxel, coordinate, 0);
		if(albedoSample != vec4(0.f)){
			albedo = vec3(albedoSample);
			normal = vec3(normalSample);
			pos = currentPoint;
		}
	} 
	
	fragcolor = PhongLighting(pos,normal,albedo);
	fragcolor.rgb = pow(fragcolor.rgb, vec3(1.0 / 2.2));
}
float attenuation(float d){ return 1.f/(1.f+0.1f*d+0.1f*d*d); }
vec4 PhongLighting(vec3 p, vec3 n, vec3 albedo){
	vec4 res;
	for(int i = 0; i < pointLights.length(); i++){
		vec3 l = pointLights[i].pos - p;
		float dist = length(l);
		l = normalize(l);
		float att = attenuation(dist);
		vec3 v = normalize(camPos - p);
		vec3 r = reflect(-l, n);
		vec3 lightColor = pointLights[i].color * att*((0.3f + 1.f*max(0,dot(n,l))+pow(max(0,dot(r,v)), 10.0f)));
		res += vec4(albedo*lightColor, 1.0f);
	}
	return res;
}