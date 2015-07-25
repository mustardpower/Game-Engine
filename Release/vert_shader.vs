#version 110

attribute vec3 position;
attribute vec2 tex_coords;

uniform mat4 mvp_matrix;
varying vec2 t_coords;

void main( void )
{
	t_coords = tex_coords;
	gl_Position = mvp_matrix * vec4(position, 1.0);
}