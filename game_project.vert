#version 400

layout (location=0) in vec3 vp; // points
layout (location=1) in vec3 vn; // normals
layout (location=2) in vec2 vt; // texture points

uniform mat4 M, V, P;

out vec3 normal_eye, position_eye;

out vec2 texture_coordinates;

void main () {
	position_eye = vec3(V * M * vec4(vp, 1.0));
	normal_eye = vec3(V * M * vec4(vn, 0.0));
	gl_Position = P * vec4 (position_eye, 1.0);

	texture_coordinates = vt;
}
