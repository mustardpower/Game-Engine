#version 330

out vec4 colorOut;

varying vec3 fragNormal;

void main()
{
    colorOut = vec4(fragNormal,1.0);
}
