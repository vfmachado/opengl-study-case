#version 430
	
in vec3 v_normal;
in vec2 v_textureCoord;
in vec3 v_fragpos;

out vec4 fragColor;

uniform vec3 color;	
uniform vec3 lightPosition;

uniform sampler2D mytexture;

void main(void) {

	vec3 norm = normalize(v_normal);
	vec3 lightDirection = normalize(v_fragpos - lightPosition);  
	
	float diff = max(dot(norm, lightDirection), 0.0);

	fragColor =  texture(mytexture, v_textureCoord) * vec4(color, 1.0) * diff;
	
	fragColor =  texture(mytexture, v_textureCoord);

}
