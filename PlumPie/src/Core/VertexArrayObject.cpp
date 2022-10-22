#include "VertexArrayObject.hpp"
#include <iostream>

namespace Plum::GL
{
	VertexArrayObject::VertexArrayObject()
	{
		glGenVertexArrays(1, &m_vaoID);
	}

	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteVertexArrays(1, &m_vaoID);
	}

	void VertexArrayObject::Bind()
	{
		glBindVertexArray(m_vaoID);
	}

	void VertexArrayObject::EnableAttribute(unsigned int index, int size, unsigned int offset, const void* data)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, offset, data);
	}

}

