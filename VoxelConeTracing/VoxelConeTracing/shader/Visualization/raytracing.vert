#version 450 core         

layout(location = 0) in vec3 pos_attrib;
layout(location = 2) in vec2 tex_coord_attrib;
out vec2 tex_coord; 

void main(){
	tex_coord = tex_coord_attrib;
	gl_Position = vec4(pos_attrib, 1);
}