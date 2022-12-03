// https://blog.lapingames.com/draw-circle-glsl-shader/
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 value;

out vec2 val;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    val = value;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}