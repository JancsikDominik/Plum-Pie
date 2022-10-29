#include "VertexArrayObject.hpp"
#include <Debug/Debug.hpp>

namespace Plum::GL
{
	VertexArrayObject::VertexArrayObject()
	{
		GL_CALL(glGenVertexArrays(1, &m_vaoID));
	}

	VertexArrayObject::~VertexArrayObject()
	{
		GL_CALL(glDeleteVertexArrays(1, &m_vaoID));
	}

	void VertexArrayObject::Bind()
	{
		GL_CALL(glBindVertexArray(m_vaoID));
	}

	void VertexArrayObject::EnableAttribute(unsigned int index, int size, unsigned int offset, const void* data)
	{
		GL_CALL(glEnableVertexAttribArray(index));
		GL_CALL(glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, offset, data));
	}

}

