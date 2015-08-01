#version 140

in vec2 TexCoord0;
out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1,TexCoord0.st);
}
