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


/*
* @TODO grid rendering references
* - https://madebyevan.com/shaders/grid/
* - https://github.com/martin-pr/possumwood/wiki/Infinite-ground-plane-using-GLSL-shaders
* - http://asliceofrendering.com/scene%20helper/2020/01/05/InfiniteGrid/
*/
void main()
{
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    FragColor = vec4(color.r, color.g, color.b, color.a);
}