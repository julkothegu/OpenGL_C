#include "Mesh.h"

Mesh::Mesh(std::vector<Def3> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Textures loader)
{
	Vertices = vertices;
	Indices = indices;
	Texturess = textures;
	Loader = loader;

	setupMesh();
}

void Mesh::draw(Shader shader)
{
	unsigned int specularNum = 1;
	unsigned int diffuseNum = 1;
	unsigned int normalNum = 1;
	unsigned int heightNum = 1;
	std::string number;
	std::string finalName;

	std::string tex = "material.";
	
	for (unsigned int i = 0; i < Texturess.size(); i++)
	{
		std::string name = Texturess[i].type;

		if (std::strcmp(name.c_str(), "specular") == 0)
		{
			number = std::to_string(specularNum++);
		}
		else if (std::strcmp(name.c_str(), "diffuse") == 0)
		{
			number = std::to_string(diffuseNum++);
		}
		else if (std::strcmp(name.c_str(), "normal") == 0)
		{
			number = std::to_string(normalNum++);
		}
		else if (std::strcmp(name.c_str(), "height") == 0)
		{
			number = std::to_string(heightNum++);
		}

		unsigned int texNum = Textures::returnSize();

		glActiveTexture(GL_TEXTURE0 + i + texNum);
		glBindTexture(GL_TEXTURE_2D, Texturess[i].id);

		finalName = (tex + Texturess[i].type).c_str();

		shader.setInt(finalName, i + texNum);
	}

	VAO.bind();
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, nullptr);

	glActiveTexture(0);
}

void Mesh::setupMesh()
{
	VAO = Context();
	VBO = VertexBuffer(Vertices.size() * sizeof(Def3), &Vertices[0], 's', "type3a", GL_FALSE, GL_FLOAT);
	EBO = VertexBuffer(Indices.size() * sizeof(unsigned int), &Indices[0], 's', "EBO", GL_FALSE, GL_FLOAT);
	
	VAO.addBuffer(VBO, "VBO");

	VAO.setVBOAttribs();

	
}
