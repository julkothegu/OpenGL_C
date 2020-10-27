#pragma once

#include "DataDefs.h"
#include <vector>
#include <iostream>
#include "Shader.h"
#include <string>
#include <cstring>
#include "Textures.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "Mesh.h"
#include "Context.h"

class Model 
{
public: 
	Model(const std::string &path);

	void draw(Shader shader);
	void loadModel(const std::string &path);
private:
	std::vector<Mesh> Meshes;
	std::string Directory;
	std::vector <Texture> LoadedTextures;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> processTexture(aiMaterial* mat, aiTextureType type, std::string typeName, Textures &tex);
};