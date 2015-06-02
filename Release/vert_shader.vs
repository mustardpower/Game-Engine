#version 330

in vec3 position;
in vec3 normal;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

varying vec3 fragNormal;

void main( void )
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	fragNormal = normal;
}