#version 450 core
in vec3 pos;

out vec4 fragcolor;

void main(){ 
	fragcolor = vec4(pos, 1); 
}