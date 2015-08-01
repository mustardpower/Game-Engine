#version 140

in vec3 position;
in vec2 TexCoord;

out vec2 TexCoord0;

uniform mat4 mvp_matrix;

void main( void )
{
	TexCoord0 = TexCoord;
	gl_Position = mvp_matrix * vec4(position, 1.0);
}