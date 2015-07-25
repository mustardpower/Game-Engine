#version 140

uniform sampler2D texture1;
in vec2 t_coords;

void main()
{
    gl_FragColor = texture2D(texture1, t_coords.st);
}
