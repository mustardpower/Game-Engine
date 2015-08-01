#version 140

in vec2 TexCoord0;

uniform sampler2D texture1;

void main()
{
    gl_FragColor = texture(texture1, TexCoord0.st);
}
