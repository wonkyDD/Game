#version 460 core
out vec4 FragColor;
//layout(location = 0) out vec4 FragColor;

uniform float time;

//in vec3 ourColor;
in vec2 ourPos;

void main()
{
    //vec3 col = 0.5 + 0.5 * cos(time + ourPos.xyx);
    vec3 col = 0.5 + 0.5 * cos(time + ourPos.xyx + vec3(0, 2, 4));
    FragColor = vec4(col, 1.0);


    //float radius = 0.1;
    //float borderThickness = 0.1;
    //vec4 color = vec4(1.0, 0.0, 0.0, 1.0);
    //vec2 position = vec2(0.0, 0.0);
    //vec2 uv = gl_FragCoord.xy - position;
    //float d = sqrt(dot(uv, uv));

    //float t = 1.0 - smoothstep(0.0, borderThickness, abs(radius - d));
    //FragColor = vec4(color.rgb, color.a * t);
}
