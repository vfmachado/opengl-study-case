#version 430
	
in vec3 v_normal;

out vec4 fragColor;

uniform vec3 color;	
uniform vec3 lightDirection;

void main(void) {

	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(-lightDirection);  
	
	float diff = max(dot(norm, lightDir), 0.0);

	fragColor =  vec4(color, 1.0) * diff;
	
}
