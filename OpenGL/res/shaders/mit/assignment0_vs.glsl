#version 430

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 normal;

uniform mat4 MVP;
uniform mat4 model;

out vec3 v_normal;


void main(void) {

	vec3 vertexPos = vertexPosition;

	gl_Position = MVP * vec4(vertexPos, 1.0);

	v_normal = (model * vec4(normal, 1)).xyz;
}
