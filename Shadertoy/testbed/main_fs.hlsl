#version 460 core
out vec4 FragColor;

// iTime�� ����
uniform float time;

in vec3 ourColor;
in vec2 ourPos;

void main()
{
    // vec3 col = 0.5 + 0.5 * cos(time + ourPos.xyx);
    vec3 col = 0.5 + 0.5 * cos(time + ourPos.xyx + vec3(0, 2, 4));

    // @TODO ����� �ٸ��� �̻��� ���
    //vec3 col = 0.5 + 0.5 * cos(time + gl_FragCoord.xyx + vec3(0, 2, 4));
    FragColor = vec4(col, 1.0);
}