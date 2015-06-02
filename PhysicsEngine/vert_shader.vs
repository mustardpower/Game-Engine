#version 140

in vec3 position;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main( void )
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = projection * view * model * vec4(position, 1.0);
}