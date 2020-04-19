#version 450 core
#define MAX_LIGHT 10
#define STEP_LENGTH 0.01f
#define MAX_STEPS 3.0f/STEP_LENGTH
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
uniform sampler3D albedoVoxel;
uniform sampler3D normalVoxel;
uniform vec3 camPos;

in vec3 pos;
in vec3 normal;
in vec2 tex_coord;

out vec4 fragcolor;

vec3 PhongLightingDiffuse(PointLight light);
vec3 IndirectDiffuse();

vec3 shift(vec3 p){ return 0.5*p + vec3(0.5); }
bool isInsideCube(const vec3 p, float e) { return abs(p.x) < 1 + e && abs(p.y) < 1 + e && abs(p.z) < 1 + e; }

void main(void)
{   
	vec3 directDiffuse = vec3(0);
	for(int i = 0; i<pointLights.length();i++){
		directDiffuse += PhongLightingDiffuse(pointLights[i]);
	}
	fragcolor = vec4(directDiffuse + IndirectDiffuse(), 1.0);
}


float attenuation(float d){ return 1.f/(1.f+0.5f*d+0.5f*d*d); }
vec3 PhongLightingDiffuse(PointLight light){
	vec3 l = light.pos - pos;
	float dist = length(l);
	l = normalize(l);
	float att = attenuation(dist);
	vec3 lightColor = att*material.diffuseColor*material.diffuseReflectivity*(max(0,dot(normal,l)));
	return lightColor*light.color;
}

struct Cone{
	vec3 origin;
	vec3 dir;
	float angle;
	int getMipmapLevel(int steps){
		float dist = tan(angle/2.f)*steps*STEP_LENGTH;
		return int(mix(0, 7, dist));
	}
};
vec4 TraceIndirectDiffuse(Cone cone){
	vec4 res = vec4(0);
	for(int steps = 4; steps < MAX_STEPS; steps++){
		vec3 p = cone.origin + steps*STEP_LENGTH*cone.dir;
		vec3 coord = shift(p);
		vec4 diffuseSample = textureLod(albedoVoxel, coord, cone.getMipmapLevel(steps));
		res += diffuseSample * attenuation(length(p - cone.origin));

		if(res.a>=1.0f || !isInsideCube(p,0))
			return res;
	}
	return res;
}
vec3 IndirectDiffuse(){
	Cone cones[9];
	
	vec3 bNormal = normalize(cross(normal, vec3(1,1,1)));
	cones[0].dir = normal;
	cones[1].dir = normalize(normal + bNormal);
	cones[2].dir = normalize(normal - bNormal);
	vec3 t = normalize(cross(normal, bNormal));
	cones[3].dir = normalize(normal + t);
	cones[4].dir = normalize(normal - t);

	cones[5].dir = normalize(normal + bNormal + t);
	cones[6].dir = normalize(normal + bNormal - t);
	cones[7].dir = normalize(normal - bNormal + t);
	cones[8].dir = normalize(normal - bNormal - t);

	vec4 indirectDiffuce = vec4(0);
	for(int i = 0; i < 9; i++){
		cones[i].origin = pos;
		cones[i].angle = 90.f;
		if(i == 0)
			indirectDiffuce += 0.25f*TraceIndirectDiffuse(cones[i]);
		else
			indirectDiffuce += 0.75f / 8.f * TraceIndirectDiffuse(cones[i]);
	}
	return vec3(indirectDiffuce);
}

















