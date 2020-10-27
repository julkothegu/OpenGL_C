#pragma once

#include <iostream>
#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "Textures.h"

 struct Arg2
{
    float x; float y;
};

 struct Arg3
{
    float x; float y; float z;
};

 struct Arg4
{
    float x; float y; float z; float w;
};

 struct Def1
 {
     Arg3 position;
 };

 struct Def2 {
    Arg3 position;
    Arg2 texPos;
};

 struct Def2C {
     Arg3 position;
     Arg2 color;
 };

 struct Texture {
     unsigned int id;
     std::string type;
     aiString path;
 };

 struct Def3 {
    Arg3 position;
    Arg3 normal;
    Arg2 texPos;
};

 struct Def5 {
     Arg3 position;
     Arg3 normal;
     Arg2 texPos;
     Arg3 tanNormal;
     Arg3 height;
 };

 struct AttribInfo
 {
     unsigned int id;
     std::string def;
     int size;
     GLenum type;
     GLboolean normalized;
 };

 struct LightInfo
 {
     float constant;
     float linear;
     float quadratic;
 };

 extern std::array<Def2, 8> createCube(float x1, float y1, float z1, float a1, float a2, float size);