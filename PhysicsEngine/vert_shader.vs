in vec3 position;
in vec2 tex_coords;

uniform mat4 mvp_matrix;

void main( void )
{
	gl_TexCoord[0] = vec4(tex_coords,0.0,0.0);
	gl_Position = mvp_matrix * vec4(position, 1.0);
}