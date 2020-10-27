#include "Context.h"

Context::Context()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
}

void Context::bind()
{
	glBindVertexArray(vertexArray);
}

void Context::unbind()
{
	glBindVertexArray(0);
}

void Context::addBuffer(VertexBuffer buffer, std::string def)
{
	unsigned int id = buffer.returnBuffer(def);
	attrib.id = id;
	attrib.size = buffer.Size;
	attrib.normalized = buffer.Normalized;
	attrib.type = buffer.Type;
	attrib.def = buffer.Def;
}

void Context::setVBOAttribs()
{
	if (attrib.def == "type5a")
	{
		GLCall(glVertexAttribPointer(0, 3, attrib.type, attrib.normalized, sizeof(Def5), (void*)offsetof(Def5, position)));
		GLCall(glEnableVertexAttribArray(0));

		GLCall(glVertexAttribPointer(1, 3, attrib.type, attrib.normalized, sizeof(Def5), (void*)offsetof(Def5, normal)));
		GLCall(glEnableVertexAttribArray(1));

		GLCall(glVertexAttribPointer(2, 2, attrib.type, attrib.normalized, sizeof(Def5), (void*)offsetof(Def5, texPos)));
		GLCall(glEnableVertexAttribArray(2));

		GLCall(glVertexAttribPointer(3, 3, attrib.type, attrib.normalized, sizeof(Def5), (void*)offsetof(Def5, tanNormal)));
		GLCall(glEnableVertexAttribArray(3));

		GLCall(glVertexAttribPointer(4, 3, attrib.type, attrib.normalized, sizeof(Def5), (void*)offsetof(Def5, height)));
		GLCall(glEnableVertexAttribArray(4));
	}
	else if (attrib.def == "type3a")
	{
		GLCall(glVertexAttribPointer(0, 3, attrib.type, attrib.normalized, sizeof(Def3), (void*)offsetof(Def3, position)));
		GLCall(glEnableVertexAttribArray(0));

		GLCall(glVertexAttribPointer(1, 3, attrib.type, attrib.normalized, sizeof(Def3), (void*)offsetof(Def3, normal)));
		GLCall(glEnableVertexAttribArray(1));

		GLCall(glVertexAttribPointer(2, 2, attrib.type, attrib.normalized, sizeof(Def3), (void*)offsetof(Def3, texPos)));
		GLCall(glEnableVertexAttribArray(2));
	}
	else if (attrib.def == "type2a")
	{
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Def2), (void*)offsetof(Def2, position)));
		GLCall(glEnableVertexAttribArray(0));

		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Def2), (void*)offsetof(Def2, texPos)));
		GLCall(glEnableVertexAttribArray(1));
	}
	else if (attrib.def == "type2b")
	{
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Def2), (void*)offsetof(Def2C, position)));
		GLCall(glEnableVertexAttribArray(0));

		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Def2), (void*)offsetof(Def2C, color)));
		GLCall(glEnableVertexAttribArray(1));
	}
	else if (attrib.def == "type1a")
	{
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Def1), (void*)offsetof(Def1, position)));
		GLCall(glEnableVertexAttribArray(0));
	}
}

unsigned int Context::getID()
{
	return vertexArray;
}
