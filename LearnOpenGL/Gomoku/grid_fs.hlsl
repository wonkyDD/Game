#version 460 core
out vec4 FragColor;

struct Color
{
    float r;
    float g;
    float b;
    float a;
};

// https://www.schemecolor.com/weird-rainbow.php
uniform Color color;

void main()
{
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    FragColor = vec4(color.r, color.g, color.b, color.a);
}