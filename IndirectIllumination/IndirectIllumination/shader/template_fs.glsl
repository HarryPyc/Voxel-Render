#version 400
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
uniform sampler2D tex;
out vec4 fragcolor;     

in vec3 pos;
in vec3 normal;
in vec2 tex_coord;
     
vec3 PhongLightingModel(PointLight light);
void main(void)
{   
	vec3 lightColor = material.emissivity*material.diffuseColor;
	for(int i = 0; i < pointLights.length(); i++){
		lightColor += PhongLightingModel(pointLights[i]);
	}
	
	fragcolor = texture2D(tex, tex_coord) * vec4(lightColor,1);
}

float attenuation(float d){ return 1.f/(1.f+0.1f*d+0.1f*d*d); }
vec3 PhongLightingModel(PointLight light){
	vec3 l = light.pos - pos;
	float dist = length(l);
	l = normalize(l);
	float att = attenuation(dist);
	vec3 v = normalize(camPos - pos);
	vec3 r = reflect(-l,normal);

	vec3 lightColor = 0.3f*material.diffuseColor + att*(material.diffuseColor*material.diffuseReflectivity*max(0,dot(normal,l))
		+ material.specularColor*material.specularReflectivity*pow(max(0,dot(r,v)),material.shiness));
	return lightColor*light.color;
}


















