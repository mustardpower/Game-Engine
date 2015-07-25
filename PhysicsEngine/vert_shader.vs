#version 140

in vec3 position;

uniform mat4 mvp_matrix;

void main( void )
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = mvp_matrix * vec4(position, 1.0);
}