#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int size, void* data, char draw, std::string def, GLboolean normalized, GLenum type)
{
	Size = size;
	Def = def;
	Normalized = normalized;
	Type = type;

	if (Def == "EBO")
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, data, GL_STATIC_DRAW));
		return;
	}
	else
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	if (draw == 'd')
		glBufferData(GL_ARRAY_BUFFER, Size, data, GL_DYNAMIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, Size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bindEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbindEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::returnBuffer(std::string def)
{
	return ID;
}

void VertexBuffer::printlala()
{
	std::cout << "VertexBuffaaaa" << std::endl;
}

unsigned int VertexBuffer::getID()
{
	return ID;
}

