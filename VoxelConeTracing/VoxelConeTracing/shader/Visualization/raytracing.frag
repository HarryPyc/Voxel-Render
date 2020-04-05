#version 450 core

#define STEP_LENGTH 0.005f
#define INV_STEP_LENGTH (1.0f/STEP_LENGTH)

uniform sampler2D fbo_texture0; //back texture
uniform sampler2D fbo_texture1; //front texture
uniform sampler3D VoxelTexture; 
uniform vec3 camPos; 

in vec2 tex_coord; 
out vec4 fragcolor;

// get 3D texture coordinate.
vec3 shift(vec3 p) { return 0.5f * p + vec3(0.5f); }

bool isInsideCube(vec3 p, float e) { return abs(p.x) < 1 + e && abs(p.y) < 1 + e && abs(p.z) < 1 + e; }

void main(void) {
	// Initialize ray.
	vec3 origin = isInsideCube(camPos, 0.2f) ? camPos 
	: texture(fbo_texture1, tex_coord).xyz;
	vec3 dir = texture(fbo_texture0, tex_coord).xyz - origin;
	const uint Steps = uint(INV_STEP_LENGTH * length(dir));
	dir = normalize(dir);

	// Trace.
	fragcolor = vec4(0);
	for(int i = 0; i < Steps && fragcolor.a < 0.99f; i++) {
		const vec3 currentPoint = origin + STEP_LENGTH * i * dir;
		vec3 coordinate = shift(currentPoint);
		vec4 currentSample = textureLod(VoxelTexture, shift(currentPoint), 0);
		fragcolor += (1.0f - fragcolor.a) * currentSample;
	} 
	fragcolor.rgb = pow(fragcolor.rgb, vec3(1.0 / 2.2));
	
}