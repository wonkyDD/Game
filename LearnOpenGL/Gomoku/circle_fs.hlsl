// https://blog.lapingames.com/draw-circle-glsl-shader/
#version 460 core
in vec2 val;

out vec4 FragColor;

void main()
{
    float R = 1.0;
    float R2 = 0.5;
    float dist = sqrt(dot(val, val));
    if (dist >= R || dist <= R2) 
    {
        discard;
    }

    float sm = smoothstep(R, R - 0.01, dist);
    float sm2 = smoothstep(R2, R2 + 0.01, dist);
    float alpha = sm * sm2;

    FragColor = vec4(1.0, 1.0, 0.0, alpha);
}