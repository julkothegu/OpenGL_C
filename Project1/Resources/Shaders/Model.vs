#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texPos;

out vec3 Color;
out vec3 Normal;
out vec3 FragPos;
out vec3 Poso;
out vec2 TexPos;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;

uniform vec3 color;

void main()
{
	FragPos = vec3(model * vec4(pos, 1.0));
	Normal = mat3(transpose(inverse(model))) * normals;
	TexPos = texPos;
	Color = color;
	Poso = pos;
	gl_Position = projection * view * model * vec4(FragPos, 1.0);
}