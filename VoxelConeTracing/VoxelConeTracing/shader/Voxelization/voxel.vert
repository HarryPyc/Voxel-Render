#version 450 core            
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

layout(location = 0)in vec3 pos_attrib;
layout(location = 1)in vec3 normal_attrib;
layout(location = 2)in vec2 tex_coord_attrib;

out vec3 pos;
out vec3 normal;
out vec2 tex_coord;

void main(void){
	pos = vec3(M*vec4(pos_attrib,1.0));
	gl_Position = P*V*vec4(pos, 1.0);
	normal = normalize(mat3(transpose(inverse(M))) * normal_attrib);
	tex_coord = tex_coord_attrib;
}