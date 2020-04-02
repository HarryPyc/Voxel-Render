#version 400            
uniform mat4 PV;
uniform mat4 M;

layout(location = 0)in vec3 pos_attrib;
layout(location = 1)in vec3 normal_attrib;
layout(location = 2)in vec2 tex_coord_attrib;

out vec3 pos;
out vec3 normal;
out vec2 tex_coord;  

void main(void)
{
   gl_Position = PV*M*vec4(pos_attrib, 1.0);
   pos = vec3(M*vec4(pos_attrib, 1.0));
   tex_coord = tex_coord_attrib;
   normal = vec3(M*vec4(normal_attrib,0));
   normal = normalize(normal);
}