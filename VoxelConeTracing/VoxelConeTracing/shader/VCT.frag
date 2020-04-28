#version 450 core
#define MAX_LIGHT 10
#define STEP_LENGTH 0.01f
#define MAX_STEPS (2.0f/STEP_LENGTH)
#define MAX_LEVEL 6.0f
#define Vlength (2/128.f)
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
uniform	float directDiffuseFactor;
uniform	float directSpecularFactor;
uniform	float indirectDiffuseFactor;
uniform	float indirectSpecularFactor;

in vec3 pos;
in vec3 normal;
in vec2 tex_coord;

out vec4 fragcolor;

vec3 PhongLightingDiffuse(PointLight light);
vec3 PhongLightingSpecular(PointLight light);
vec3 IndirectDiffuse();
vec3 TraceIndirectSpecular();
float TraceShadow(PointLight light);

vec3 shift(vec3 p){ return 0.5*p + vec3(0.5); }
bool isInsideCube(const vec3 p, float e) { return abs(p.x) < 1 + e && abs(p.y) < 1 + e && abs(p.z) < 1 + e; }

void main(void)
{   
	vec3 color = vec3(0);
	float shadow = TraceShadow(pointLights[0]);
	if(directDiffuseFactor>0.f)
		color += shadow * directDiffuseFactor * PhongLightingDiffuse(pointLights[0]);
	if(directSpecularFactor>0.f)
		color += shadow * directSpecularFactor * PhongLightingSpecular(pointLights[0]);
	if(indirectDiffuseFactor>0.f)
		color += indirectDiffuseFactor * IndirectDiffuse();
	if(indirectSpecularFactor>0.f);
		color += indirectSpecularFactor * TraceIndirectSpecular();

	fragcolor = vec4(color, 1.0);
//	fragcolor *= 0.5f;
}


float attenuation(float d){ return 1.f/(1.f+0.1f*d+0.1f*d*d); }
vec3 PhongLightingDiffuse(PointLight light){
	vec3 l = light.pos - pos;
	float dist = length(l);
	l = normalize(l);
	float att = attenuation(dist);
	vec3 lightColor = att*material.diffuseColor*material.diffuseReflectivity*(max(0,dot(normal,l)));
	return lightColor*light.color;
}
vec3 PhongLightingSpecular(PointLight light){
	vec3 l = pos - light.pos;
	float dist = length(l);
	l = normalize(l);
	vec3 r = reflect(l,normal);
	vec3 v = normalize(camPos - pos);
	return light.color * material.specularColor * material.specularReflectivity * attenuation(dist)*max(0,pow(dot(r,v), material.shiness));
}
struct Cone{
	vec3 origin;
	vec3 dir;
	float spread;
	float getMipmapLevel(vec3 p){
		float dist = spread*length(p-origin);
		return (log2(1+dist/Vlength));
	}
};
vec3 TraceIndirectDiffuse(Cone cone){
	vec4 res = vec4(0);
	vec3 p = cone.origin;
	while(isInsideCube(p,0) && res.a<1.f){

		vec3 coord = shift(p);
		float level = cone.getMipmapLevel(p);
		float ll = (level+1)*(level+1);
		vec4 diffuseSample = textureLod(albedoVoxel, coord, min(MAX_LEVEL, level));
		res += diffuseSample * attenuation(length(p-cone.origin));
		p += Vlength*cone.dir;
	}
	return res.rgb;
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

	vec3 indirectDiffuce = vec3(0);
	for(int i = 0; i < cones.length(); i++){
		cones[i].origin = pos + cones[i].dir*Vlength*3.f;
		cones[i].spread = 0.4f;
		indirectDiffuce += TraceIndirectDiffuse(cones[i]);
	}
	return vec3(indirectDiffuce)/9.f * material.diffuseColor * material.diffuseReflectivity;
}

float TraceShadow(PointLight light){
	Cone cone;
	cone.origin = pos + Vlength*normal;
	cone.spread = 0.05f;
	cone.dir = normalize(light.pos - pos);
	float shadow = 1.f;
	vec3 p = cone.origin + 2*Vlength*cone.dir;
	const uint maxStep = uint(length(light.pos - p) / STEP_LENGTH);
	for(int i = 0; i < maxStep; i++){
		p += cone.dir*STEP_LENGTH;
		vec3 coord = shift(p);
		vec4 albedoSample = textureLod(albedoVoxel,coord,cone.getMipmapLevel(p));
		shadow -= albedoSample.a * attenuation(i*STEP_LENGTH);
		if(shadow <=0)
			break;
	}
	return pow(smoothstep(0,1,shadow), 0.5f);
}
vec3 TraceIndirectSpecular(){
	vec3 v = normalize(pos - camPos);
	Cone cone;
	cone.origin = pos + Vlength*normal;
	cone.dir = reflect(v,normal);
	vec3 p = cone.origin + 2*Vlength*cone.dir;
	cone.spread = 0.05f;
	vec4 res = vec4(0);
	while(isInsideCube(p,0) && res.a<1.f){
		vec3 coord = shift(p);
		vec4 albedoSample = textureLod(albedoVoxel,coord,cone.getMipmapLevel(p));
		res += albedoSample * attenuation(length(p-cone.origin));
		p += cone.dir * STEP_LENGTH;
	}
	return res.rgb * material.specularReflectivity;
}














