#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 atex;
layout (location = 3) in vec2 aOffset;

uniform mat4 projection;
uniform	mat4 view;
uniform mat4 model;

out vec2 Tex;
out vec3 fragPos;
out vec3 Normal;

void main()
{
	fragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	Tex = atex;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}

