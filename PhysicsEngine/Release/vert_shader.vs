#version 140

in vec3 position;
in vec2 tex_coords;

uniform mat4 mvp_matrix;
out vec2 t_coords;

void main( void )
{
	t_coords = tex_coords;
	gl_Position = mvp_matrix * vec4(position, 1.0);
}