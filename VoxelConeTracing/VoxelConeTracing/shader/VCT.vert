#version 450 core

layout(location = 0) in vec3 pos_attrib;
layout(location = 1) in vec3 normal_attrib;

uniform mat4 M;
uniform mat4 P;
uniform mat4 V;

out vec3 pos;
out vec3 normal;

void main(){
	pos = vec3(M * vec4(pos_attrib, 1));
	normal = normalize(mat3(transpose(inverse(M))) * normal_attrib);
	gl_Position = P * V * vec4(pos, 1);
}