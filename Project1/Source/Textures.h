#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm.hpp>
#include "DataDefs.h"

class Textures
{

public:

	static unsigned int texSetUp(const std::string& filepath, std::string format, bool gamma);

    unsigned int addTex(const std::string& filepath, std::string format, bool gamma);
	unsigned int addModel(const std::string& filepath, std::string format, std::string directory, bool gamma);

	unsigned int loadCubeMap(std::vector<std::string> faces, bool gamma);

    void textureBinder(int offset);
	static unsigned int returnSize();

private:
	static std::vector<int> theVector;
	static std::vector <std::string> vectorPaths;
};
  