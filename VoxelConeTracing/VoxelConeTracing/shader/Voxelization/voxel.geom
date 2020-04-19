#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 pos[];
in vec3 normal[];
in vec2 tex_coord[];

out vec3 Pos;
out vec3 Normal;
out vec2 Tex_coord;

void main(void){
	const vec3 p1 = pos[1] - pos[0];
	const vec3 p2 = pos[2] - pos[0];
	const vec3 p = abs(cross(p1, p2)); 
	for(int i = 0; i < 3; i++){
		Pos = pos[i];
		Normal = normal[i];
		Tex_coord = tex_coord[i];
		//gl_Position = vec4(Pos,1);
		if(p.z >= p.x && p.z >= p.y){
			gl_Position = vec4(Pos.x, Pos.y, 0, 1);
		} else if (p.x >= p.y && p.x >= p.z){
			gl_Position = vec4(Pos.y, Pos.z, 0, 1);
		} else {
			gl_Position = vec4(Pos.x, Pos.z, 0, 1);
		}
		EmitVertex();
	}
    EndPrimitive();
}


