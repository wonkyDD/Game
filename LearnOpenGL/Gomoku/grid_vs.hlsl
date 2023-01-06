#version 460 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

/*
* @TODO grid rendering references
* - https://madebyevan.com/shaders/grid/
* - https://github.com/martin-pr/possumwood/wiki/Infinite-ground-plane-using-GLSL-shaders
* - http://asliceofrendering.com/scene%20helper/2020/01/05/InfiniteGrid/
*/
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}