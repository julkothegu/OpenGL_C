#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texPos;

out vec3 Color;
out vec3 Normal;
out vec3 FragPos;
out vec3 Poso;

out VS_OUT
{
	vec3 normal;
} vs_out;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	mat3 normalMatrix = mat3(transpose(inverse(view * model)));
	vs_out.normal = normalize(vec3(projection * vec4(normalMatrix * normals, 0.0)));
}