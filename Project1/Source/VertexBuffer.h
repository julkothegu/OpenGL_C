#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.h"

class VertexBuffer
{
public:
	unsigned int Size;
	std::string Def;
	GLboolean Normalized;
	GLenum Type;

	VertexBuffer(unsigned int size = 0, void* data = NULL, char draw = 'n', std::string def = "n", GLboolean normalized = false, GLenum type = NULL);
	void bind();
	void unbind();
	void bindEBO();
	void unbindEBO();
	unsigned int returnBuffer(std::string def);
	void printlala();
	unsigned int getID();
	
private:
	unsigned int ID;
};