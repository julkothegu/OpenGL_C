#pragma once

#include <iostream>
#include <vector>
#include "DataDefs.h"
#include "Shader.h"
#include "Textures.h"
#include "Context.h"
#include "VertexBuffer.h"

class Mesh
{
public:
	std::vector<Def3> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<Texture> Texturess;
	Textures Loader;

	Mesh(std::vector<Def3> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Textures loader);
	void draw(Shader shader);
private:
	void setupMesh();
	Context VAO;
	VertexBuffer VBO;
	VertexBuffer EBO;
};