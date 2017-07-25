#version 330 core

uniform vec4 color;

uniform bool    asdf1;
uniform int     asdf2;
uniform float   asdf3;

out vec4 fragColor;

void main ()
{
    float temp;
    if (asdf1) {
        temp = asdf2;
    } else {
        temp = asdf3;
    }
    fragColor = color * temp;
}

