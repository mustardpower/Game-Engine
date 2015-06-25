in vec3 position;
in vec3 norm;

uniform mat4 mvp_matrix;

out vec3 normal;

void main( void )
{
	normal = norm;
	gl_Position = mvp_matrix * vec4(position, 1.0);
}