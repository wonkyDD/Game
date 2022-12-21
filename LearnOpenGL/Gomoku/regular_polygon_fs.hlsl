#version 460 core
out vec4 FragColor;

uniform bool isBlack;
uniform float alpha;

void main()
{
    if (isBlack) FragColor = vec4(0.0, 0.0, 0.0, alpha);
    else FragColor = vec4(1.0, 1.0, 1.0, alpha);
}
