#version 330 core

uniform vec4 color;

uniform bool    asdf1;
uniform int     asdf2;
uniform float   asdf3;

// add more if required
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

// add more if required
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

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

