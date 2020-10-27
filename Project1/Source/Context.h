#pragma once

#include "VertexBuffer.h"
#include "DataDefs.h"
#include "Renderer.h"
#include <iostream>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Context
{
public:
	Context();
	void bind();
	void unbind();
	void addBuffer(VertexBuffer buffer, std::string def);
	void setVBOAttribs();
	unsigned int getID();
private:
	unsigned int vertexArray;
	AttribInfo attrib;
};