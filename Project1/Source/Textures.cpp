#include "Textures.h"
#include "stb_image.h"

std::vector<int> Textures::theVector;
std::vector <std::string> Textures::vectorPaths;

unsigned int Textures::addTex(const std::string &filepath, std::string format, bool gamma) 
{
    unsigned int ID = texSetUp(filepath, format, gamma);

    theVector.push_back(ID);
    return ID;
}

unsigned int Textures::addModel(const std::string &filepath, std::string format, std::string modelName, bool gamma)
{
    std::string filePath;
    filePath = modelName + '/'+ filepath;

    return texSetUp(filePath, format, gamma);
}

unsigned int Textures::loadCubeMap(std::vector<std::string> faces, bool gamma)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    stbi_set_flip_vertically_on_load(false);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLint format = GL_RGB;
            if (gamma)
            {
                format = GL_SRGB;
            }

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}

unsigned int Textures::texSetUp(const std::string& filepath, std::string format, bool gamma)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

    GLenum Format;
    GLint format1;

    if (gamma)
    {
        format1 = GL_SRGB;
    }

    if (data)
    {
        switch (nrChannels)
        {
        case 1:
            Format = GL_RED;
            format1 = GL_RED;
            break;
        case 3:
            Format = GL_RGB;
            format1 = GL_RGB;
            if (gamma)
            {
                format1 = GL_SRGB;
            }
            break;
        case 4:
            Format = GL_RGBA;
            format1 = GL_RGBA;
            if (gamma)
            {
                format1 = GL_SRGB_ALPHA;
            }
            break;
        default:
            std::cout << "Texture channel data invalid D:" << std::endl;
            return 1;
        }
    
        glTexImage2D(GL_TEXTURE_2D, 0, format1, width, height, 0, Format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    stbi_image_free(data);
    vectorPaths.push_back(filepath);

    return textureID;
}

void Textures::textureBinder(int offset)
{
    if (theVector.empty())
    {
        std::cout << "Vector is empty!" << std::endl;
    }

    for (size_t t = 0; t < theVector.size(); t++)
    {     
        glActiveTexture(GL_TEXTURE0 + t + offset);
        glBindTexture(GL_TEXTURE_2D, theVector[t]);
    }
}

 unsigned int Textures::returnSize()
 {
     return theVector.size();
 }


