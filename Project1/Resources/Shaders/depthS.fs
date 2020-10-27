#version 330 core

out vec4 FragColor;

void main()
{
    gl_FragDepth = gl_FragCoord.z;
    FragColor = vec4(vec3(0.0, 1.0, 0.0), 1.0);
}