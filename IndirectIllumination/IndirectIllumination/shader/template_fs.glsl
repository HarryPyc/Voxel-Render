#version 400

struct Material {
	vec3 diffuseColor;
	vec3 specularColor;
	float diffuseReflectivity;
	float specularReflectivity;
	float emissivity;
	float transparency;
};
uniform Material material;
uniform sampler2D tex;
out vec4 fragcolor;           
in vec2 tex_coord;
      
void main(void)
{   
	fragcolor = texture2D(tex, tex_coord) * vec4(material.diffuseColor,1.0);
}




















