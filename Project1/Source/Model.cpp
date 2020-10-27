#include "Model.h"

Model::Model(const std::string &path)
{
	loadModel(path);
}

void Model::draw(Shader shader)
{
	for (unsigned int i = 0; i < Meshes.size(); i++)
	{
		Meshes[i].draw(shader);
	}
}

void Model::loadModel(const std::string &path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	Directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Mesh processed = processMesh(mesh, scene);
		Meshes.push_back(processed);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Def3> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Def3 def;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		if (mesh->mVertices != NULL)
			def.position.x = mesh->mVertices[i].x;
			def.position.y = mesh->mVertices[i].y;
			def.position.z = mesh->mVertices[i].z;

		//?? ?Disabled temporarily for EARTHWROM JIMMY ???

		if (mesh->mNormals != NULL)
			def.normal.x = mesh->mNormals[i].x;
			def.normal.y = mesh->mNormals[i].y;
			def.normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			def.texPos.x = mesh->mTextureCoords[0][i].x;
			def.texPos.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			def.texPos.x = 0.0f; def.texPos.y = 0.0f;
		}
		/*

		if (mesh->mTangents && mesh->mBitangents)
		{
			def.tanNormal.x = mesh->mTangents[i].x;
			def.tanNormal.y = mesh->mTangents[i].y;
			def.tanNormal.z = mesh->mTangents[i].z;

			def.height.x = mesh->mBitangents[i].x;
			def.height.y = mesh->mBitangents[i].y;
			def.height.z = mesh->mBitangents[i].z;
		}
		*/

		vertices.push_back(def);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Textures tex;

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = processTexture(material, aiTextureType_DIFFUSE, "diffuse", tex);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = processTexture(material, aiTextureType_SPECULAR, "specular", tex);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<Texture> normalMaps = processTexture(material, aiTextureType_NORMALS, "normal", tex);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		std::vector<Texture> heightMaps = processTexture(material, aiTextureType_HEIGHT, "height", tex);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}

	return Mesh(vertices, indices, textures, tex);
}

std::vector<Texture> Model::processTexture(aiMaterial* mat, aiTextureType type, std::string typeName, Textures &loader)
{
	std::vector<Texture> textures;
	bool skip = false;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		for (int j = 0; j < LoadedTextures.size(); j++)
		{
			if (std::strcmp(str.C_Str(), LoadedTextures[j].path.data) == 0)
			{
				skip = true;
				textures.push_back(LoadedTextures[j]);
				break;
			}
		}

		if (!skip)
		{
			Texture tex;
			tex.id = loader.addModel(str.C_Str(), typeName, Directory, true);
			tex.type = typeName;
			tex.path = str;
			textures.push_back(tex);
			LoadedTextures.push_back(tex);
		}
	}

	return textures;
}
