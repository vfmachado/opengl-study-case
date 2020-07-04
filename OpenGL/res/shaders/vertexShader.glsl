#version 430

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 textureCoord;
layout(location = 2) in vec3 normal;

uniform mat4 MVP;
uniform mat4 model;

out vec3 v_normal;
out vec2 v_textureCoord;
out vec3 v_fragpos;


void main(void) {

	//vec3 vertexPos = vertexPosition + vec3( (gl_InstanceID % 10) * 10 - 45, 10 *  int(gl_InstanceID / 10), 0);

	vec3 vertexPos = vertexPosition;

	gl_Position = MVP * vec4(vertexPos, 1.0);

	v_fragpos = (model * vec4(vertexPos, 1.0)).xyz;
	v_textureCoord = textureCoord;
	v_normal = (model * vec4(normal, 1)).xyz;
}
