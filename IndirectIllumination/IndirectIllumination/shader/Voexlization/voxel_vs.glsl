#version 450            
uniform mat4 PV;
uniform mat4 M;

layout(location = 0)in vec3 pos_attrib;
layout(location = 1)in vec3 normal_attrib;
layout(location = 2)in vec2 tex_coord_attrib;

