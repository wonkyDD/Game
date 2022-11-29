#version 460 core
layout(location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec2 ourPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);

    // ourColor = aColor;
    ourPos = vec2(aPos.x, aPos.y);
}